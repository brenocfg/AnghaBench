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
struct ftrace_ops {int flags; } ;
typedef  int /*<<< orphan*/  ftrace_func_t ;

/* Variables and functions */
 scalar_t__ FTRACE_FORCE_LIST_FUNC ; 
 int FTRACE_OPS_FL_DYNAMIC ; 
 int FTRACE_OPS_FL_RCU ; 
 int /*<<< orphan*/  ftrace_ops_get_func (struct ftrace_ops*) ; 
 int /*<<< orphan*/  ftrace_ops_list_func ; 

__attribute__((used)) static ftrace_func_t ftrace_ops_get_list_func(struct ftrace_ops *ops)
{
	/*
	 * If this is a dynamic, RCU, or per CPU ops, or we force list func,
	 * then it needs to call the list anyway.
	 */
	if (ops->flags & (FTRACE_OPS_FL_DYNAMIC | FTRACE_OPS_FL_RCU) ||
	    FTRACE_FORCE_LIST_FUNC)
		return ftrace_ops_list_func;

	return ftrace_ops_get_func(ops);
}