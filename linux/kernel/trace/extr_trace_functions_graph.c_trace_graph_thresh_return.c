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
struct ftrace_graph_ret {scalar_t__ rettime; scalar_t__ calltime; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_NOTRACE_BIT ; 
 int /*<<< orphan*/  ftrace_graph_addr_finish (struct ftrace_graph_ret*) ; 
 int /*<<< orphan*/  trace_graph_return (struct ftrace_graph_ret*) ; 
 int /*<<< orphan*/  trace_recursion_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_recursion_test (int /*<<< orphan*/ ) ; 
 scalar_t__ tracing_thresh ; 

__attribute__((used)) static void trace_graph_thresh_return(struct ftrace_graph_ret *trace)
{
	ftrace_graph_addr_finish(trace);

	if (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT)) {
		trace_recursion_clear(TRACE_GRAPH_NOTRACE_BIT);
		return;
	}

	if (tracing_thresh &&
	    (trace->rettime - trace->calltime < tracing_thresh))
		return;
	else
		trace_graph_return(trace);
}