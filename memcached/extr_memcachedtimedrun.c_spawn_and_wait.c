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

/* Variables and functions */
 int EX_OSERR ; 
 int EX_SOFTWARE ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int wait_for_process (int) ; 

__attribute__((used)) static int spawn_and_wait(char **argv)
{
    int rv = EX_SOFTWARE;
    pid_t pid = fork();

    switch (pid) {
    case -1:
        perror("fork");
        rv = EX_OSERR;
        break; /* NOTREACHED */
    case 0:
        execvp(argv[0], argv);
        perror("exec");
        rv = EX_SOFTWARE;
        break; /* NOTREACHED */
    default:
        rv = wait_for_process(pid);
    }
    return rv;
}