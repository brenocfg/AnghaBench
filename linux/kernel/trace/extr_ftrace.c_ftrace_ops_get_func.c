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
struct ftrace_ops {int flags; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  ftrace_func_t ;

/* Variables and functions */
 int FTRACE_OPS_FL_RCU ; 
 int FTRACE_OPS_FL_RECURSION_SAFE ; 
 int /*<<< orphan*/  ftrace_ops_assist_func ; 

ftrace_func_t ftrace_ops_get_func(struct ftrace_ops *ops)
{
	/*
	 * If the function does not handle recursion, needs to be RCU safe,
	 * or does per cpu logic, then we need to call the assist handler.
	 */
	if (!(ops->flags & FTRACE_OPS_FL_RECURSION_SAFE) ||
	    ops->flags & FTRACE_OPS_FL_RCU)
		return ftrace_ops_assist_func;

	return ops->func;
}