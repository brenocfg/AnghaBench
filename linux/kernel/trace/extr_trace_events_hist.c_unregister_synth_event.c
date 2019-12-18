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
struct synth_event {struct trace_event_call call; } ;

/* Variables and functions */
 int trace_remove_event_call (struct trace_event_call*) ; 

__attribute__((used)) static int unregister_synth_event(struct synth_event *event)
{
	struct trace_event_call *call = &event->call;
	int ret;

	ret = trace_remove_event_call(call);

	return ret;
}