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
 scalar_t__ tracer_enabled ; 
 int /*<<< orphan*/  unregister_wakeup_function (struct trace_array*,int) ; 

__attribute__((used)) static void stop_func_tracer(struct trace_array *tr, int graph)
{
	tracer_enabled = 0;

	unregister_wakeup_function(tr, graph);
}