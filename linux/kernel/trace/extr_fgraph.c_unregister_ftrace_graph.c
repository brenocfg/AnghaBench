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
typedef  scalar_t__ trace_func_graph_ret_t ;
struct fgraph_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTRACE_STOP_FUNC_RET ; 
 void* __ftrace_graph_entry ; 
 int /*<<< orphan*/  ftrace_graph_active ; 
 void* ftrace_graph_entry ; 
 void* ftrace_graph_entry_stub ; 
 int /*<<< orphan*/  ftrace_graph_probe_sched_switch ; 
 scalar_t__ ftrace_graph_return ; 
 int /*<<< orphan*/  ftrace_lock ; 
 int /*<<< orphan*/  ftrace_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ftrace_stub ; 
 int /*<<< orphan*/  ftrace_suspend_notifier ; 
 int /*<<< orphan*/  graph_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_trace_sched_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void unregister_ftrace_graph(struct fgraph_ops *gops)
{
	mutex_lock(&ftrace_lock);

	if (unlikely(!ftrace_graph_active))
		goto out;

	ftrace_graph_active--;
	ftrace_graph_return = (trace_func_graph_ret_t)ftrace_stub;
	ftrace_graph_entry = ftrace_graph_entry_stub;
	__ftrace_graph_entry = ftrace_graph_entry_stub;
	ftrace_shutdown(&graph_ops, FTRACE_STOP_FUNC_RET);
	unregister_pm_notifier(&ftrace_suspend_notifier);
	unregister_trace_sched_switch(ftrace_graph_probe_sched_switch, NULL);

 out:
	mutex_unlock(&ftrace_lock);
}