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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char* const) ; 
 int /*<<< orphan*/  execve (char* const,char* const*,char* const*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char* const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char* const) ; 

__attribute__((used)) static int
run_script(char *const *argv, char *const *envp)
{
    pid_t pid;
    int ret = 0;

    pid = fork();
    if (pid == (pid_t)0)   /* child side */
    {
        execve(argv[0], argv, envp);
        /* If execve() fails to run, exit child with exit code 127 */
        err(127, "DOWN-ROOT: Failed execute: %s", argv[0]);
    }
    else if (pid < (pid_t)0)
    {
        warn("DOWN-ROOT: Failed to fork child to run %s", argv[0]);
        return -1;
    }
    else     /* parent side */
    {
        if (waitpid(pid, &ret, 0) != pid)
        {
            /* waitpid does not return error information via errno */
            fprintf(stderr, "DOWN-ROOT: waitpid() failed, don't know exit code of child (%s)\n", argv[0]);
            return -1;
        }
    }
    return ret;
}