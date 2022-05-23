#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct helper_args {
    char* string;
    char target;
} helper_args_t;

int counter = 0;

void fun1()
{

}

int parts_of_process()
{
    // on the stack because its a local var
    struct helper_args h;

    printf("addr of global variable: %p\n", &counter);

    printf("addr of fun1: %p\n", &fun1);
    // &: address
    // *: value
    printf("addr of stack variable: %p\n", &h);

    // heap: dynamic allocated memory
    // malloc(), free()
    helper_args_t *h1 = malloc(sizeof(helper_args_t));

    printf("addr of heap variable: %p\n", h1);
    // format string is 1st argument: %d\n
    // d: decimal
    // p: pointer
    // s: char*/string
    // c: char
    printf("sizeof=%lu\n", sizeof(helper_args_t));

    // do stuff with h1

    free(h1);

    return 0;
}

int fork_ex()
{
    int a = 4;
    printf("a in parent %d = %d\n", getpid(), a);

    int child_pid = fork();

    if (child_pid < 0)
        printf("fork failed\n");
    else if (child_pid) // parent
    {
        waitpid(child_pid, NULL, 0);
        printf("child_pid=%d\n", child_pid);
        printf("a in parent %d = %d\n", getpid(), a);
        exit(0);
    }
    else // child
    {
        a = 5;
        printf("a in child %d = %d\n", getpid(), a);
        exit(0);
    }
}

void* thread_func(void *arg)
{
    int *num = (int*)arg;
    *num = 6;
    printf("[child thread] num=%d process=%d\n", *num, getpid());
    return 0;
}

void thread_ex()
{
    pthread_t p;
    int num = 5;
    printf("[main thread] num=%d process=%d\n", num, getpid());
    int ret = pthread_create(&p, NULL, thread_func, &num);

    if (ret != 0)
    {
        printf("thread creation failed\n");
        exit(1);
    }

    pthread_join(p, NULL);
    printf("[main thread] num=%d process=%d\n", num, getpid());

}

int main()
{
    // parts_of_process();
    // fork_ex();
    thread_ex();
}
