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
struct trace_array {int /*<<< orphan*/ * function_pids; } ;
struct ftrace_ops {int flags; struct trace_array* private; } ;

/* Variables and functions */
 int FTRACE_OPS_FL_PID ; 

__attribute__((used)) static bool ftrace_pids_enabled(struct ftrace_ops *ops)
{
	struct trace_array *tr;

	if (!(ops->flags & FTRACE_OPS_FL_PID) || !ops->private)
		return false;

	tr = ops->private;

	return tr->function_pids != NULL;
}