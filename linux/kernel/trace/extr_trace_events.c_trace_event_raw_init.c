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
struct trace_event_call {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int ENODEV ; 
 int register_trace_event (int /*<<< orphan*/ *) ; 

int trace_event_raw_init(struct trace_event_call *call)
{
	int id;

	id = register_trace_event(&call->event);
	if (!id)
		return -ENODEV;

	return 0;
}