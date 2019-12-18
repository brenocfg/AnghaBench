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
 int /*<<< orphan*/  BP_X ; 
 int COUNT_ISN_BPS ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  check_success (char*) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/ * dummy_funcs ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_breakpoint_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  toggle_breakpoint (int,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void launch_instruction_breakpoints(char *buf, int local, int global)
{
	int i;

	for (i = 0; i < COUNT_ISN_BPS; i++) {
		set_breakpoint_addr(dummy_funcs[i], i);
		toggle_breakpoint(i, BP_X, 1, local, global, 1);
		ptrace(PTRACE_CONT, child_pid, NULL, 0);
		sprintf(buf, "Test breakpoint %d with local: %d global: %d\n",
			i, local, global);
		check_success(buf);
		toggle_breakpoint(i, BP_X, 1, local, global, 0);
	}
}