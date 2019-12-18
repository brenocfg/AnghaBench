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
 int register_ftrace_graph (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_graph_array (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 
 scalar_t__ tracing_thresh ; 

__attribute__((used)) static int graph_trace_init(struct trace_array *tr)
{
	int ret;

	set_graph_array(tr);
	if (tracing_thresh)
		ret = register_ftrace_graph(&funcgraph_thresh_ops);
	else
		ret = register_ftrace_graph(&funcgraph_ops);
	if (ret)
		return ret;
	tracing_start_cmdline_record();

	return 0;
}