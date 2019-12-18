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
struct perf_event_attr {scalar_t__ exclude_kernel; } ;
struct perf_event {int dummy; } ;
struct arch_hw_breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ arch_check_bp_in_kernelspace (struct arch_hw_breakpoint*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int hw_breakpoint_arch_parse (struct perf_event*,struct perf_event_attr const*,struct arch_hw_breakpoint*) ; 

__attribute__((used)) static int hw_breakpoint_parse(struct perf_event *bp,
			       const struct perf_event_attr *attr,
			       struct arch_hw_breakpoint *hw)
{
	int err;

	err = hw_breakpoint_arch_parse(bp, attr, hw);
	if (err)
		return err;

	if (arch_check_bp_in_kernelspace(hw)) {
		if (attr->exclude_kernel)
			return -EINVAL;
		/*
		 * Don't let unprivileged users set a breakpoint in the trap
		 * path to avoid trap recursion attacks.
		 */
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
	}

	return 0;
}