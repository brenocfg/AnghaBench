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
struct ftrace_ops {int flags; int /*<<< orphan*/  func; int /*<<< orphan*/  saved_func; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FTRACE_OPS_FL_DELETED ; 
 int FTRACE_OPS_FL_DYNAMIC ; 
 int FTRACE_OPS_FL_ENABLED ; 
 int FTRACE_OPS_FL_SAVE_REGS ; 
 int FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  add_ftrace_ops (int /*<<< orphan*/ *,struct ftrace_ops*) ; 
 int /*<<< orphan*/  core_kernel_data (unsigned long) ; 
 scalar_t__ ftrace_enabled ; 
 int /*<<< orphan*/  ftrace_ops_list ; 
 int /*<<< orphan*/  ftrace_pid_func ; 
 scalar_t__ ftrace_pids_enabled (struct ftrace_ops*) ; 
 int /*<<< orphan*/  ftrace_update_trampoline (struct ftrace_ops*) ; 
 int /*<<< orphan*/  update_ftrace_function () ; 

int __register_ftrace_function(struct ftrace_ops *ops)
{
	if (ops->flags & FTRACE_OPS_FL_DELETED)
		return -EINVAL;

	if (WARN_ON(ops->flags & FTRACE_OPS_FL_ENABLED))
		return -EBUSY;

#ifndef CONFIG_DYNAMIC_FTRACE_WITH_REGS
	/*
	 * If the ftrace_ops specifies SAVE_REGS, then it only can be used
	 * if the arch supports it, or SAVE_REGS_IF_SUPPORTED is also set.
	 * Setting SAVE_REGS_IF_SUPPORTED makes SAVE_REGS irrelevant.
	 */
	if (ops->flags & FTRACE_OPS_FL_SAVE_REGS &&
	    !(ops->flags & FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED))
		return -EINVAL;

	if (ops->flags & FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED)
		ops->flags |= FTRACE_OPS_FL_SAVE_REGS;
#endif

	if (!core_kernel_data((unsigned long)ops))
		ops->flags |= FTRACE_OPS_FL_DYNAMIC;

	add_ftrace_ops(&ftrace_ops_list, ops);

	/* Always save the function, and reset at unregistering */
	ops->saved_func = ops->func;

	if (ftrace_pids_enabled(ops))
		ops->func = ftrace_pid_func;

	ftrace_update_trampoline(ops);

	if (ftrace_enabled)
		update_ftrace_function();

	return 0;
}