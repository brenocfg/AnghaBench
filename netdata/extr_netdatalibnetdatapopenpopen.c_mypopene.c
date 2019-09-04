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
 size_t PIPE_READ ; 
 size_t PIPE_WRITE ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execle (char*,char*,char*,char const*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int fork () ; 
 int pipe (int*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

FILE *mypopene(const char *command, volatile pid_t *pidptr, char **env) {
    int pipefd[2];

    if(pipe(pipefd) == -1)
        return NULL;

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

    execle("/bin/sh", "sh", "-c", command, NULL, env);
    exit(1);
}