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
struct ftrace_ops {int flags; int /*<<< orphan*/  saved_func; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int EBUSY ; 
 int FTRACE_OPS_FL_ENABLED ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ftrace_enabled ; 
 int /*<<< orphan*/  ftrace_ops_list ; 
 int remove_ftrace_ops (int /*<<< orphan*/ *,struct ftrace_ops*) ; 
 int /*<<< orphan*/  update_ftrace_function () ; 

int __unregister_ftrace_function(struct ftrace_ops *ops)
{
	int ret;

	if (WARN_ON(!(ops->flags & FTRACE_OPS_FL_ENABLED)))
		return -EBUSY;

	ret = remove_ftrace_ops(&ftrace_ops_list, ops);

	if (ret < 0)
		return ret;

	if (ftrace_enabled)
		update_ftrace_function();

	ops->func = ops->saved_func;

	return 0;
}