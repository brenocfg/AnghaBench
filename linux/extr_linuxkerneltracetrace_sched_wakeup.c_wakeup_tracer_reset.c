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
 int TRACE_ITER_LATENCY_FMT ; 
 int TRACE_ITER_OVERWRITE ; 
 int /*<<< orphan*/  ftrace_reset_array_ops (struct trace_array*) ; 
 int save_flags ; 
 int /*<<< orphan*/  set_tracer_flag (struct trace_array*,int,int) ; 
 int /*<<< orphan*/  stop_wakeup_tracer (struct trace_array*) ; 
 int wakeup_busy ; 
 int /*<<< orphan*/  wakeup_reset (struct trace_array*) ; 

__attribute__((used)) static void wakeup_tracer_reset(struct trace_array *tr)
{
	int lat_flag = save_flags & TRACE_ITER_LATENCY_FMT;
	int overwrite_flag = save_flags & TRACE_ITER_OVERWRITE;

	stop_wakeup_tracer(tr);
	/* make sure we put back any tasks we are tracing */
	wakeup_reset(tr);

	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, lat_flag);
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, overwrite_flag);
	ftrace_reset_array_ops(tr);
	wakeup_busy = false;
}