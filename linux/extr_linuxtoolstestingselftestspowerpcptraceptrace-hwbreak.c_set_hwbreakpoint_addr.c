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
struct ppc_hw_breakpoint {int version; scalar_t__ condition_value; void* addr2; void* addr; int /*<<< orphan*/  condition_mode; int /*<<< orphan*/  addr_mode; int /*<<< orphan*/  trigger_type; } ;
typedef  void* __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_BREAKPOINT_CONDITION_NONE ; 
 int /*<<< orphan*/  PPC_BREAKPOINT_MODE_EXACT ; 
 int /*<<< orphan*/  PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE ; 
 int /*<<< orphan*/  PPC_BREAKPOINT_TRIGGER_RW ; 
 int /*<<< orphan*/  PPC_PTRACE_SETHWDEBUG ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ppc_hw_breakpoint*) ; 

__attribute__((used)) static int set_hwbreakpoint_addr(void *addr, int range)
{
	int ret;

	struct ppc_hw_breakpoint info;

	info.version = 1;
	info.trigger_type = PPC_BREAKPOINT_TRIGGER_RW;
	info.addr_mode = PPC_BREAKPOINT_MODE_EXACT;
	if (range > 0)
		info.addr_mode = PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE;
	info.condition_mode = PPC_BREAKPOINT_CONDITION_NONE;
	info.addr = (__u64)addr;
	info.addr2 = (__u64)addr + range;
	info.condition_value = 0;

	ret = ptrace(PPC_PTRACE_SETHWDEBUG, child_pid, 0, &info);
	if (ret < 0) {
		perror("Can't set breakpoint\n");
		exit(-1);
	}
	return ret;
}