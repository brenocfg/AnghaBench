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
struct trace_array {int /*<<< orphan*/  ops; scalar_t__ function_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_ftrace_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracing_stop_function_trace(struct trace_array *tr)
{
	tr->function_enabled = 0;
	unregister_ftrace_function(tr->ops);
}