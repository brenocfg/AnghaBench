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
struct ftrace_graph_ent {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int __ftrace_graph_entry (struct ftrace_graph_ent*) ; 
 int /*<<< orphan*/  ftrace_ops_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_ops ; 

__attribute__((used)) static int ftrace_graph_entry_test(struct ftrace_graph_ent *trace)
{
	if (!ftrace_ops_test(&global_ops, trace->func, NULL))
		return 0;
	return __ftrace_graph_entry(trace);
}