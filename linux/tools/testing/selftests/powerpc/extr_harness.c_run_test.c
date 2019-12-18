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
 scalar_t__ EINTR ; 
 int KILL_TIMEOUT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  alarm (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setpgid (int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int timeout ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int run_test(int (test_function)(void), char *name)
{
	bool terminated;
	int rc, status;
	pid_t pid;

	/* Make sure output is flushed before forking */
	fflush(stdout);

	pid = fork();
	if (pid == 0) {
		setpgid(0, 0);
		exit(test_function());
	} else if (pid == -1) {
		perror("fork");
		return 1;
	}

	setpgid(pid, pid);

	if (timeout != -1)
		/* Wake us up in timeout seconds */
		alarm(timeout);
	terminated = false;

wait:
	rc = waitpid(pid, &status, 0);
	if (rc == -1) {
		if (errno != EINTR) {
			printf("unknown error from waitpid\n");
			return 1;
		}

		if (terminated) {
			printf("!! force killing %s\n", name);
			kill(-pid, SIGKILL);
			return 1;
		} else {
			printf("!! killing %s\n", name);
			kill(-pid, SIGTERM);
			terminated = true;
			alarm(KILL_TIMEOUT);
			goto wait;
		}
	}

	/* Kill anything else in the process group that is still running */
	kill(-pid, SIGTERM);

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else {
		if (WIFSIGNALED(status))
			printf("!! child died by signal %d\n", WTERMSIG(status));
		else
			printf("!! child died by unknown cause\n");

		status = 1; /* Signal or other */
	}

	return status;
}