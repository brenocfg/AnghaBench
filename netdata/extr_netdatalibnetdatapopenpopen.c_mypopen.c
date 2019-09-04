#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  D_CHILDS ; 
 size_t PIPE_READ ; 
 size_t PIPE_WRITE ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  signals_reset () ; 
 int /*<<< orphan*/  signals_unblock () ; 
 int sysconf (int /*<<< orphan*/ ) ; 

FILE *mypopen(const char *command, volatile pid_t *pidptr)
{
    int pipefd[2];

    if(pipe(pipefd) == -1) return NULL;

    int pid = fork();
    if(pid == -1) {
        close(pipefd[PIPE_READ]);
        close(pipefd[PIPE_WRITE]);
        return NULL;
    }
    if(pid != 0) {
        // the parent
        *pidptr = pid;
        close(pipefd[PIPE_WRITE]);
        FILE *fp = fdopen(pipefd[PIPE_READ], "r");
        /*mypopen_add(fp, pid);*/
        return(fp);
    }
    // the child

    // close all files
    int i;
    for(i = (int) (sysconf(_SC_OPEN_MAX) - 1); i >= 0; i--)
        if(i != STDIN_FILENO && i != STDERR_FILENO && i != pipefd[PIPE_WRITE]) close(i);

    // move the pipe to stdout
    if(pipefd[PIPE_WRITE] != STDOUT_FILENO) {
        dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
        close(pipefd[PIPE_WRITE]);
    }

#ifdef DETACH_PLUGINS_FROM_NETDATA
    // this was an attempt to detach the child and use the suspend mode charts.d
    // unfortunatelly it does not work as expected.

    // fork again to become session leader
    pid = fork();
    if(pid == -1)
        error("pre-execution of command '%s' on pid %d: Cannot fork 2nd time.", command, getpid());

    if(pid != 0) {
        // the parent
        exit(0);
    }

    // set a new process group id for just this child
    if( setpgid(0, 0) != 0 )
        error("pre-execution of command '%s' on pid %d: Cannot set a new process group.", command, getpid());

    if( getpgid(0) != getpid() )
        error("pre-execution of command '%s' on pid %d: Cannot set a new process group. Process group set is incorrect. Expected %d, found %d", command, getpid(), getpid(), getpgid(0));

    if( setsid() != 0 )
        error("pre-execution of command '%s' on pid %d: Cannot set session id.", command, getpid());

    fprintf(stdout, "MYPID %d\n", getpid());
    fflush(NULL);
#endif

    // reset all signals
    signals_unblock();
    signals_reset();

    debug(D_CHILDS, "executing command: '%s' on pid %d.", command, getpid());
    execl("/bin/sh", "sh", "-c", command, NULL);
    exit(1);
}