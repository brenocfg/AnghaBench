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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  event_filter_pid_sched_process_exit ; 
 int /*<<< orphan*/  event_filter_pid_sched_process_fork ; 
 int /*<<< orphan*/  register_trace_prio_sched_process_exit (int /*<<< orphan*/ ,struct trace_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_trace_prio_sched_process_fork (int /*<<< orphan*/ ,struct trace_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_trace_sched_process_exit (int /*<<< orphan*/ ,struct trace_array*) ; 
 int /*<<< orphan*/  unregister_trace_sched_process_fork (int /*<<< orphan*/ ,struct trace_array*) ; 

void trace_event_follow_fork(struct trace_array *tr, bool enable)
{
	if (enable) {
		register_trace_prio_sched_process_fork(event_filter_pid_sched_process_fork,
						       tr, INT_MIN);
		register_trace_prio_sched_process_exit(event_filter_pid_sched_process_exit,
						       tr, INT_MAX);
	} else {
		unregister_trace_sched_process_fork(event_filter_pid_sched_process_fork,
						    tr);
		unregister_trace_sched_process_exit(event_filter_pid_sched_process_exit,
						    tr);
	}
}