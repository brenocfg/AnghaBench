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
 int /*<<< orphan*/  exit (int) ; 
 int test_vmx (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  varray ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

int vmx_syscall(void)
{
	pid_t fork_pid;
	int i;
	int ret;
	int child_ret;
	for (i = 0; i < 1000; i++) {
		/* test_vmx will fork() */
		ret = test_vmx(varray, &fork_pid);
		if (fork_pid == -1)
			return -1;
		if (fork_pid == 0)
			exit(ret);
		waitpid(fork_pid, &child_ret, 0);
		if (ret || child_ret)
			return 1;
	}

	return 0;
}