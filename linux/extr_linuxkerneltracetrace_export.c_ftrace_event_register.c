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
struct trace_event_call {int dummy; } ;
typedef  enum trace_reg { ____Placeholder_trace_reg } trace_reg ;

/* Variables and functions */

__attribute__((used)) static int ftrace_event_register(struct trace_event_call *call,
				 enum trace_reg type, void *data)
{
	return 0;
}