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
struct trace_array {scalar_t__ max_latency; int /*<<< orphan*/  trace_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_ITER_LATENCY_FMT ; 
 int /*<<< orphan*/  TRACE_ITER_OVERWRITE ; 
 int /*<<< orphan*/  ftrace_init_array_ops (struct trace_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_flags ; 
 int /*<<< orphan*/  set_tracer_flag (struct trace_array*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_wakeup_tracer (struct trace_array*) ; 
 int wakeup_busy ; 
 struct trace_array* wakeup_trace ; 
 int /*<<< orphan*/  wakeup_tracer_call ; 

__attribute__((used)) static int __wakeup_tracer_init(struct trace_array *tr)
{
	save_flags = tr->trace_flags;

	/* non overwrite screws up the latency tracers */
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, 1);
	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, 1);

	tr->max_latency = 0;
	wakeup_trace = tr;
	ftrace_init_array_ops(tr, wakeup_tracer_call);
	start_wakeup_tracer(tr);

	wakeup_busy = true;
	return 0;
}