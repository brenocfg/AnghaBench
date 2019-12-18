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
struct ppc_debug_info {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_RW ; 
 int /*<<< orphan*/  BP_W ; 
 int PPC_DEBUG_FEATURE_DATA_BP_RANGE ; 
 int /*<<< orphan*/  PPC_PTRACE_GETHWDBGINFO ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 scalar_t__ SIGTRAP ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  launch_watchpoints (char*,int /*<<< orphan*/ ,int,struct ppc_debug_info*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ppc_debug_info*) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static int launch_tests(bool dawr)
{
	char buf[1024];
	int len, i, status;

	struct ppc_debug_info dbginfo;

	i = ptrace(PPC_PTRACE_GETHWDBGINFO, child_pid, NULL, &dbginfo);
	if (i) {
		perror("Can't set breakpoint info\n");
		exit(-1);
	}
	if (!(dbginfo.features & PPC_DEBUG_FEATURE_DATA_BP_RANGE))
		printf("WARNING: Kernel doesn't support PPC_PTRACE_SETHWDEBUG\n");

	/* Write watchpoint */
	for (len = 1; len <= sizeof(long); len <<= 1)
		launch_watchpoints(buf, BP_W, len, &dbginfo, dawr);

	/* Read-Write watchpoint */
	for (len = 1; len <= sizeof(long); len <<= 1)
		launch_watchpoints(buf, BP_RW, len, &dbginfo, dawr);

	ptrace(PTRACE_CONT, child_pid, NULL, 0);

	/*
	 * Now we have unregistered the breakpoint, access by child
	 * should not cause SIGTRAP.
	 */

	wait(&status);

	if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
		printf("FAIL: Child process hit the breakpoint, which is not expected\n");
		ptrace(PTRACE_CONT, child_pid, NULL, 0);
		return TEST_FAIL;
	}

	if (WIFEXITED(status))
		printf("Child exited normally\n");

	return TEST_PASS;
}