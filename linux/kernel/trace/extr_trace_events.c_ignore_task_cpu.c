#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_pid_list {int dummy; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct trace_array {TYPE_2__ trace_buffer; int /*<<< orphan*/  filtered_pids; } ;
struct TYPE_3__ {int /*<<< orphan*/  ignore_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct trace_pid_list* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ignore_this_task (struct trace_pid_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ignore_task_cpu(void *data)
{
	struct trace_array *tr = data;
	struct trace_pid_list *pid_list;

	/*
	 * This function is called by on_each_cpu() while the
	 * event_mutex is held.
	 */
	pid_list = rcu_dereference_protected(tr->filtered_pids,
					     mutex_is_locked(&event_mutex));

	this_cpu_write(tr->trace_buffer.data->ignore_pid,
		       trace_ignore_this_task(pid_list, current));
}