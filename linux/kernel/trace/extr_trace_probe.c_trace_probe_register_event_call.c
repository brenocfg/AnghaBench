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
struct trace_probe {int dummy; } ;
struct trace_event_call {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int ENODEV ; 
 int register_trace_event (int /*<<< orphan*/ *) ; 
 int trace_add_event_call (struct trace_event_call*) ; 
 struct trace_event_call* trace_probe_event_call (struct trace_probe*) ; 
 int /*<<< orphan*/  unregister_trace_event (int /*<<< orphan*/ *) ; 

int trace_probe_register_event_call(struct trace_probe *tp)
{
	struct trace_event_call *call = trace_probe_event_call(tp);
	int ret;

	ret = register_trace_event(&call->event);
	if (!ret)
		return -ENODEV;

	ret = trace_add_event_call(call);
	if (ret)
		unregister_trace_event(&call->event);

	return ret;
}