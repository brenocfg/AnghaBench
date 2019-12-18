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
struct task_struct {unsigned long long ftrace_timestamp; int curr_ret_stack; TYPE_1__* ret_stack; } ;
struct TYPE_2__ {unsigned long long calltime; } ;

/* Variables and functions */
 scalar_t__ fgraph_sleep_time ; 
 unsigned long long trace_clock_local () ; 

__attribute__((used)) static void
ftrace_graph_probe_sched_switch(void *ignore, bool preempt,
			struct task_struct *prev, struct task_struct *next)
{
	unsigned long long timestamp;
	int index;

	/*
	 * Does the user want to count the time a function was asleep.
	 * If so, do not update the time stamps.
	 */
	if (fgraph_sleep_time)
		return;

	timestamp = trace_clock_local();

	prev->ftrace_timestamp = timestamp;

	/* only process tasks that we timestamped */
	if (!next->ftrace_timestamp)
		return;

	/*
	 * Update all the counters in next to make up for the
	 * time next was sleeping.
	 */
	timestamp -= next->ftrace_timestamp;

	for (index = next->curr_ret_stack; index >= 0; index--)
		next->ret_stack[index].calltime += timestamp;
}