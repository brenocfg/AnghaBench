#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_pid_list {int dummy; } ;
struct trace_event_file {struct trace_array* tr; } ;
struct trace_array_cpu {int ignore_pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct trace_array {TYPE_1__ trace_buffer; int /*<<< orphan*/  filtered_pids; } ;

/* Variables and functions */
 struct trace_pid_list* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 struct trace_array_cpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 

bool trace_event_ignore_this_pid(struct trace_event_file *trace_file)
{
	struct trace_array *tr = trace_file->tr;
	struct trace_array_cpu *data;
	struct trace_pid_list *pid_list;

	pid_list = rcu_dereference_raw(tr->filtered_pids);
	if (!pid_list)
		return false;

	data = this_cpu_ptr(tr->trace_buffer.data);

	return data->ignore_pid;
}