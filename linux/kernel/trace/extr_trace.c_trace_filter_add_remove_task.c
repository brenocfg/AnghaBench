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
struct trace_pid_list {scalar_t__ pid_max; int /*<<< orphan*/  pids; } ;
struct task_struct {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_find_filtered_pid (struct trace_pid_list*,scalar_t__) ; 

void trace_filter_add_remove_task(struct trace_pid_list *pid_list,
				  struct task_struct *self,
				  struct task_struct *task)
{
	if (!pid_list)
		return;

	/* For forks, we only add if the forking task is listed */
	if (self) {
		if (!trace_find_filtered_pid(pid_list, self->pid))
			return;
	}

	/* Sorry, but we don't support pid_max changing after setting */
	if (task->pid >= pid_list->pid_max)
		return;

	/* "self" is set for forks, and NULL for exits */
	if (self)
		set_bit(task->pid, pid_list->pids);
	else
		clear_bit(task->pid, pid_list->pids);
}