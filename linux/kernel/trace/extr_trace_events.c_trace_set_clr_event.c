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
 int ENODEV ; 
 int __ftrace_set_clr_event (struct trace_array*,int /*<<< orphan*/ *,char const*,char const*,int) ; 
 struct trace_array* top_trace_array () ; 

int trace_set_clr_event(const char *system, const char *event, int set)
{
	struct trace_array *tr = top_trace_array();

	if (!tr)
		return -ENODEV;

	return __ftrace_set_clr_event(tr, NULL, system, event, set);
}