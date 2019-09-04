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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_SETVSRREGS ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

int write_vsx(pid_t child, unsigned long *vsx)
{
	int ret;

	ret = ptrace(PTRACE_SETVSRREGS, child, 0, vsx);
	if (ret) {
		perror("ptrace(PTRACE_SETVSRREGS) failed");
		return TEST_FAIL;
	}
	return TEST_PASS;
}