#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

void err_sys(char *p) { perror(p); exit(-1); }

int main(int ac, char *av[])
{
    int i;
    for (i = 1; i < ac; i++)
        do_cmd(av[i]); /* once for each command-line arg */
    exit(0);
}

static void do_cmd(char *cmd) /* execute and time the "cmd" */
{
    struct  tms tmsstart, tmsend;
    clock_t start, end;
    int     status;

    printf("\ncommand: %s\n", cmd);

    if ((start = times(&tmsstart)) == -1) /* starting values */
        err_sys("times error");
    
    if ((status = system(cmd)) < 0) /* execute command */
        err_sys("system() error");

    if ((end = times(&tmsend)) == -1) /* ending values */
        err_sys("times error");

    pr_times(end-start, &tmsstart, &tmsend);
}