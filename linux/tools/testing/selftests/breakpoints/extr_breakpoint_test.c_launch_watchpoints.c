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
 int BP_W ; 
 int COUNT_WPS ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  check_success (char*) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/ * dummy_var ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_breakpoint_addr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  toggle_breakpoint (int,int,int,int,int,int) ; 

__attribute__((used)) static void launch_watchpoints(char *buf, int mode, int len,
			       int local, int global)
{
	const char *mode_str;
	int i;

	if (mode == BP_W)
		mode_str = "write";
	else
		mode_str = "read";

	for (i = 0; i < COUNT_WPS; i++) {
		set_breakpoint_addr(&dummy_var[i], i);
		toggle_breakpoint(i, mode, len, local, global, 1);
		ptrace(PTRACE_CONT, child_pid, NULL, 0);
		sprintf(buf,
			"Test %s watchpoint %d with len: %d local: %d global: %d\n",
			mode_str, i, len, local, global);
		check_success(buf);
		toggle_breakpoint(i, mode, len, local, global, 0);
	}
}