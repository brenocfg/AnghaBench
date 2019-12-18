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

/* Variables and functions */
 int /*<<< orphan*/  BP_RW ; 
 int /*<<< orphan*/  BP_W ; 
 int COUNT_ISN_BPS ; 
 int COUNT_WPS ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  check_success (char*) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  ksft_set_plan (unsigned int) ; 
 int /*<<< orphan*/  launch_instruction_breakpoints (char*,int,int) ; 
 int /*<<< orphan*/  launch_watchpoints (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void launch_tests(void)
{
	char buf[1024];
	unsigned int tests = 0;
	int len, local, global, i;

	tests += 3 * COUNT_ISN_BPS;
	tests += sizeof(long) / 2 * 3 * COUNT_WPS;
	tests += sizeof(long) / 2 * 3 * COUNT_WPS;
	tests += 2;
	ksft_set_plan(tests);

	/* Instruction breakpoints */
	for (local = 0; local < 2; local++) {
		for (global = 0; global < 2; global++) {
			if (!local && !global)
				continue;
			launch_instruction_breakpoints(buf, local, global);
		}
	}

	/* Write watchpoint */
	for (len = 1; len <= sizeof(long); len <<= 1) {
		for (local = 0; local < 2; local++) {
			for (global = 0; global < 2; global++) {
				if (!local && !global)
					continue;
				launch_watchpoints(buf, BP_W, len,
						   local, global);
			}
		}
	}

	/* Read-Write watchpoint */
	for (len = 1; len <= sizeof(long); len <<= 1) {
		for (local = 0; local < 2; local++) {
			for (global = 0; global < 2; global++) {
				if (!local && !global)
					continue;
				launch_watchpoints(buf, BP_RW, len,
						   local, global);
			}
		}
	}

	/* Icebp traps */
	ptrace(PTRACE_CONT, child_pid, NULL, 0);
	check_success("Test icebp\n");

	/* Int 3 traps */
	ptrace(PTRACE_CONT, child_pid, NULL, 0);
	check_success("Test int 3 trap\n");

	ptrace(PTRACE_CONT, child_pid, NULL, 0);
}