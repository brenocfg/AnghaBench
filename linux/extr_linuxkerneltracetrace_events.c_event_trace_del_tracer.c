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
struct trace_array {int /*<<< orphan*/ * event_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ftrace_clear_event_pids (struct trace_array*) ; 
 int /*<<< orphan*/  __ftrace_set_clr_event_nolock (struct trace_array*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __trace_remove_event_dirs (struct trace_array*) ; 
 int /*<<< orphan*/  clear_event_triggers (struct trace_array*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_event_sem ; 
 int /*<<< orphan*/  tracefs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int event_trace_del_tracer(struct trace_array *tr)
{
	lockdep_assert_held(&event_mutex);

	/* Disable any event triggers and associated soft-disabled events */
	clear_event_triggers(tr);

	/* Clear the pid list */
	__ftrace_clear_event_pids(tr);

	/* Disable any running events */
	__ftrace_set_clr_event_nolock(tr, NULL, NULL, NULL, 0);

	/* Make sure no more events are being executed */
	tracepoint_synchronize_unregister();

	down_write(&trace_event_sem);
	__trace_remove_event_dirs(tr);
	tracefs_remove_recursive(tr->event_dir);
	up_write(&trace_event_sem);

	tr->event_dir = NULL;

	return 0;
}