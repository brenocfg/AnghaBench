#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {int si_int; int /*<<< orphan*/  si_code; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  PTRACE_KILL ; 
 int SIGNR ; 
 int /*<<< orphan*/  SIGRTMIN ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  TEST_SICODE_PRIV ; 
 int /*<<< orphan*/  TEST_SICODE_SHARE ; 
 scalar_t__ check_direct_path (int,int,int) ; 
 scalar_t__ check_error_paths (int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int fork () ; 
 int getppid () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sys_ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_rt_sigqueueinfo (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sys_rt_tgsigqueueinfo (int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	siginfo_t siginfo[SIGNR];
	int i, exit_code = 1;
	sigset_t blockmask;
	pid_t child;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &blockmask, NULL);

	child = fork();
	if (child == -1) {
		err("fork() failed: %m");
		return 1;
	} else if (child == 0) {
		pid_t ppid = getppid();
		while (1) {
			if (ppid != getppid())
				break;
			sleep(1);
		}
		return 1;
	}

	/* Send signals in process-wide and per-thread queues */
	for (i = 0; i < SIGNR; i++) {
		siginfo->si_code = TEST_SICODE_SHARE;
		siginfo->si_int = i;
		sys_rt_sigqueueinfo(child, SIGRTMIN, siginfo);

		siginfo->si_code = TEST_SICODE_PRIV;
		siginfo->si_int = i;
		sys_rt_tgsigqueueinfo(child, child, SIGRTMIN, siginfo);
	}

	if (sys_ptrace(PTRACE_ATTACH, child, NULL, NULL) == -1)
		return 1;

	waitpid(child, NULL, 0);

	/* Dump signals one by one*/
	if (check_direct_path(child, 0, 1))
		goto out;
	/* Dump all signals for one call */
	if (check_direct_path(child, 0, SIGNR))
		goto out;

	/*
	 * Dump signal from the process-wide queue.
	 * The number of signals is not multible to the buffer size
	 */
	if (check_direct_path(child, 1, 3))
		goto out;

	if (check_error_paths(child))
		goto out;

	printf("PASS\n");
	exit_code = 0;
out:
	if (sys_ptrace(PTRACE_KILL, child, NULL, NULL) == -1)
		return 1;

	waitpid(child, NULL, 0);

	return exit_code;
}