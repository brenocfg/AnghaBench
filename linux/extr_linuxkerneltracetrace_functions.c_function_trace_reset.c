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
 int /*<<< orphan*/  ftrace_reset_array_ops (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_stop_cmdline_record () ; 
 int /*<<< orphan*/  tracing_stop_function_trace (struct trace_array*) ; 

__attribute__((used)) static void function_trace_reset(struct trace_array *tr)
{
	tracing_stop_function_trace(tr);
	tracing_stop_cmdline_record();
	ftrace_reset_array_ops(tr);
}