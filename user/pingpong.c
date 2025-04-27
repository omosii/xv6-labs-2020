// user/pingpong.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
    // create two pipes, pf2c for communicate form father to child
    int pf2c[2], pc2f[2];
    pipe(pf2c);
    pipe(pc2f);
    //
    if (fork() != 0)
    { // father process
        // send a symbol to child process
        write(pf2c[1], ".", 1);
        close(pf2c[1]);
        // read a symbol from child process
        char buf;
        read(pc2f[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        // wait
        wait(0);
    }
    else
    { // child process
        char buf;
        read(pf2c[0], &buf, 1);
        // printf("Process: %d, received ping symbol : %c \n", getpid(), buf);
        printf("%d: received ping\n", getpid());

        write(pc2f[1], &buf, 1);
        close(pc2f[1]);
    }

    // close pipe read end
    close(pc2f[0]);
    close(pf2c[0]);

    exit(0);
}