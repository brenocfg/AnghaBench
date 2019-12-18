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
struct trace_pid_list {int dummy; } ;
struct trace_array {int /*<<< orphan*/  filtered_pids; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct trace_pid_list* rcu_dereference_sched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_filter_add_remove_task (struct trace_pid_list*,struct task_struct*,struct task_struct*) ; 

__attribute__((used)) static void
event_filter_pid_sched_process_fork(void *data,
				    struct task_struct *self,
				    struct task_struct *task)
{
	struct trace_pid_list *pid_list;
	struct trace_array *tr = data;

	pid_list = rcu_dereference_sched(tr->filtered_pids);
	trace_filter_add_remove_task(pid_list, self, task);
}