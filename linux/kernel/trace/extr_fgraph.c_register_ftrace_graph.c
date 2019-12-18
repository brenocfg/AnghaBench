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
struct fgraph_ops {int /*<<< orphan*/  entryfunc; int /*<<< orphan*/  retfunc; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FTRACE_START_FUNC_RET ; 
 int /*<<< orphan*/  __ftrace_graph_entry ; 
 scalar_t__ ftrace_graph_active ; 
 int /*<<< orphan*/  ftrace_graph_entry ; 
 int /*<<< orphan*/  ftrace_graph_entry_test ; 
 int /*<<< orphan*/  ftrace_graph_return ; 
 int /*<<< orphan*/  ftrace_lock ; 
 int ftrace_startup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_suspend_notifier ; 
 int /*<<< orphan*/  graph_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_pm_notifier (int /*<<< orphan*/ *) ; 
 int start_graph_tracing () ; 
 int /*<<< orphan*/  update_function_graph_func () ; 

int register_ftrace_graph(struct fgraph_ops *gops)
{
	int ret = 0;

	mutex_lock(&ftrace_lock);

	/* we currently allow only one tracer registered at a time */
	if (ftrace_graph_active) {
		ret = -EBUSY;
		goto out;
	}

	register_pm_notifier(&ftrace_suspend_notifier);

	ftrace_graph_active++;
	ret = start_graph_tracing();
	if (ret) {
		ftrace_graph_active--;
		goto out;
	}

	ftrace_graph_return = gops->retfunc;

	/*
	 * Update the indirect function to the entryfunc, and the
	 * function that gets called to the entry_test first. Then
	 * call the update fgraph entry function to determine if
	 * the entryfunc should be called directly or not.
	 */
	__ftrace_graph_entry = gops->entryfunc;
	ftrace_graph_entry = ftrace_graph_entry_test;
	update_function_graph_func();

	ret = ftrace_startup(&graph_ops, FTRACE_START_FUNC_RET);
out:
	mutex_unlock(&ftrace_lock);
	return ret;
}