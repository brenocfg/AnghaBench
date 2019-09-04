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
typedef  scalar_t__ u32 ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 scalar_t__ TRACE_GRAPH_GRAPH_TIME ; 
 scalar_t__ TRACE_GRAPH_PRINT_IRQS ; 
 scalar_t__ TRACE_GRAPH_SLEEP_TIME ; 
 int /*<<< orphan*/  ftrace_graph_graph_time_control (int) ; 
 int ftrace_graph_skip_irqs ; 
 int /*<<< orphan*/  ftrace_graph_sleep_time_control (int) ; 

__attribute__((used)) static int
func_graph_set_flag(struct trace_array *tr, u32 old_flags, u32 bit, int set)
{
	if (bit == TRACE_GRAPH_PRINT_IRQS)
		ftrace_graph_skip_irqs = !set;

	if (bit == TRACE_GRAPH_SLEEP_TIME)
		ftrace_graph_sleep_time_control(set);

	if (bit == TRACE_GRAPH_GRAPH_TIME)
		ftrace_graph_graph_time_control(set);

	return 0;
}