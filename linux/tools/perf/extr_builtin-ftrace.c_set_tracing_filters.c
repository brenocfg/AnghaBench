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
struct perf_ftrace {int /*<<< orphan*/  nograph_funcs; int /*<<< orphan*/  graph_funcs; int /*<<< orphan*/  notrace; int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 int __set_tracing_filter (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_tracing_filters(struct perf_ftrace *ftrace)
{
	int ret;

	ret = __set_tracing_filter("set_ftrace_filter", &ftrace->filters);
	if (ret < 0)
		return ret;

	ret = __set_tracing_filter("set_ftrace_notrace", &ftrace->notrace);
	if (ret < 0)
		return ret;

	ret = __set_tracing_filter("set_graph_function", &ftrace->graph_funcs);
	if (ret < 0)
		return ret;

	/* old kernels do not have this filter */
	__set_tracing_filter("set_graph_notrace", &ftrace->nograph_funcs);

	return ret;
}