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
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int start_trace(pid_t child)
{
	int ret;

	ret = ptrace(PTRACE_ATTACH, child, NULL, NULL);
	if (ret) {
		perror("ptrace(PTRACE_ATTACH) failed");
		return TEST_FAIL;
	}
	ret = waitpid(child, NULL, 0);
	if (ret != child) {
		perror("waitpid() failed");
		return TEST_FAIL;
	}
	return TEST_PASS;
}