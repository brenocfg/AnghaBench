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
struct trace_array {int nr_topts; struct trace_array* name; int /*<<< orphan*/  tracing_cpumask; struct trace_array* topts; int /*<<< orphan*/  dir; int /*<<< orphan*/  list; TYPE_1__* current_trace; scalar_t__ ref; } ;
struct TYPE_2__ {scalar_t__ ref; } ;

/* Variables and functions */
 int EBUSY ; 
 int TRACE_FLAGS_MAX_SIZE ; 
 int ZEROED_TRACE_FLAGS ; 
 int /*<<< orphan*/  clear_ftrace_function_probes (struct trace_array*) ; 
 int /*<<< orphan*/  event_trace_del_tracer (struct trace_array*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_trace_buffers (struct trace_array*) ; 
 int /*<<< orphan*/  ftrace_clear_pids (struct trace_array*) ; 
 int /*<<< orphan*/  ftrace_destroy_function_files (struct trace_array*) ; 
 int /*<<< orphan*/  kfree (struct trace_array*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_tracer_flag (struct trace_array*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracefs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_set_nop (struct trace_array*) ; 

__attribute__((used)) static int __remove_instance(struct trace_array *tr)
{
	int i;

	if (tr->ref || (tr->current_trace && tr->current_trace->ref))
		return -EBUSY;

	list_del(&tr->list);

	/* Disable all the flags that were enabled coming in */
	for (i = 0; i < TRACE_FLAGS_MAX_SIZE; i++) {
		if ((1 << i) & ZEROED_TRACE_FLAGS)
			set_tracer_flag(tr, 1 << i, 0);
	}

	tracing_set_nop(tr);
	clear_ftrace_function_probes(tr);
	event_trace_del_tracer(tr);
	ftrace_clear_pids(tr);
	ftrace_destroy_function_files(tr);
	tracefs_remove_recursive(tr->dir);
	free_trace_buffers(tr);

	for (i = 0; i < tr->nr_topts; i++) {
		kfree(tr->topts[i].topts);
	}
	kfree(tr->topts);

	free_cpumask_var(tr->tracing_cpumask);
	kfree(tr->name);
	kfree(tr);
	tr = NULL;

	return 0;
}