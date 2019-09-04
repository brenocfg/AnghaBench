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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void continue_as_child(void) {
    pid_t child = fork();
    int status;
    pid_t ret;

    if (child < 0)
        error("fork() failed");

    /* Only the child returns */
    if (child == 0)
        return;

    for (;;) {
        ret = waitpid(child, &status, WUNTRACED);
        if ((ret == child) && (WIFSTOPPED(status))) {
            /* The child suspended so suspend us as well */
            kill(getpid(), SIGSTOP);
            kill(child, SIGCONT);
        } else {
            break;
        }
    }

    /* Return the child's exit code if possible */
    if (WIFEXITED(status)) {
        exit(WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        kill(getpid(), WTERMSIG(status));
    }

    exit(EXIT_FAILURE);
}