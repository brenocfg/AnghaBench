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
 int /*<<< orphan*/  funcgraph_ops ; 
 int /*<<< orphan*/  funcgraph_thresh_ops ; 
 int /*<<< orphan*/  tracing_stop_cmdline_record () ; 
 scalar_t__ tracing_thresh ; 
 int /*<<< orphan*/  unregister_ftrace_graph (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void graph_trace_reset(struct trace_array *tr)
{
	tracing_stop_cmdline_record();
	if (tracing_thresh)
		unregister_ftrace_graph(&funcgraph_thresh_ops);
	else
		unregister_ftrace_graph(&funcgraph_ops);
}