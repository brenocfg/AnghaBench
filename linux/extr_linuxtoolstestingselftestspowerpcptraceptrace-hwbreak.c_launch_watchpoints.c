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
 int BP_W ; 
 int DAWR_LENGTH_MAX ; 
 int PPC_DEBUG_FEATURE_DATA_BP_RANGE ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  check_success (char*) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  del_hwbreakpoint_addr (int) ; 
 scalar_t__ dummy_var ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_breakpoint_addr (void*) ; 
 int set_hwbreakpoint_addr (void*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 

__attribute__((used)) static void launch_watchpoints(char *buf, int mode, int len,
			       struct ppc_debug_info *dbginfo, bool dawr)
{
	const char *mode_str;
	unsigned long data = (unsigned long)(dummy_var);
	int wh, range;

	data &= ~0x7UL;

	if (mode == BP_W) {
		data |= (1UL << 1);
		mode_str = "write";
	} else {
		data |= (1UL << 0);
		data |= (1UL << 1);
		mode_str = "read";
	}

	/* Set DABR_TRANSLATION bit */
	data |= (1UL << 2);

	/* use PTRACE_SET_DEBUGREG breakpoints */
	set_breakpoint_addr((void *)data);
	ptrace(PTRACE_CONT, child_pid, NULL, 0);
	sprintf(buf, "Test %s watchpoint with len: %d ", mode_str, len);
	check_success(buf);
	/* Unregister hw brkpoint */
	set_breakpoint_addr(NULL);

	data = (data & ~7); /* remove dabr control bits */

	/* use PPC_PTRACE_SETHWDEBUG breakpoint */
	if (!(dbginfo->features & PPC_DEBUG_FEATURE_DATA_BP_RANGE))
		return; /* not supported */
	wh = set_hwbreakpoint_addr((void *)data, 0);
	ptrace(PTRACE_CONT, child_pid, NULL, 0);
	sprintf(buf, "Test %s watchpoint with len: %d ", mode_str, len);
	check_success(buf);
	/* Unregister hw brkpoint */
	del_hwbreakpoint_addr(wh);

	/* try a wider range */
	range = 8;
	if (dawr)
		range = 512 - ((int)data & (DAWR_LENGTH_MAX - 1));
	wh = set_hwbreakpoint_addr((void *)data, range);
	ptrace(PTRACE_CONT, child_pid, NULL, 0);
	sprintf(buf, "Test %s watchpoint with len: %d ", mode_str, len);
	check_success(buf);
	/* Unregister hw brkpoint */
	del_hwbreakpoint_addr(wh);
}