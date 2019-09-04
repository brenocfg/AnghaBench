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
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int vmx_syscall () ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

int test_vmx_syscall(void)
{
	/*
	 * Setup an environment with much context switching
	 */
	pid_t pid2;
	pid_t pid = fork();
	int ret;
	int child_ret;
	FAIL_IF(pid == -1);

	pid2 = fork();
	ret = vmx_syscall();
	/* Can't FAIL_IF(pid2 == -1); because we've already forked */
	if (pid2 == -1) {
		/*
		 * Couldn't fork, ensure child_ret is set and is a fail
		 */
		ret = child_ret = 1;
	} else {
		if (pid2)
			waitpid(pid2, &child_ret, 0);
		else
			exit(ret);
	}

	ret |= child_ret;

	if (pid)
		waitpid(pid, &child_ret, 0);
	else
		exit(ret);

	FAIL_IF(ret || child_ret);
	return 0;
}