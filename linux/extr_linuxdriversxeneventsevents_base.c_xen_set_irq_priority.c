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
struct evtchn_set_priority {unsigned int priority; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_set_priority ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_set_priority*) ; 
 int /*<<< orphan*/  evtchn_from_irq (unsigned int) ; 

int xen_set_irq_priority(unsigned irq, unsigned priority)
{
	struct evtchn_set_priority set_priority;

	set_priority.port = evtchn_from_irq(irq);
	set_priority.priority = priority;

	return HYPERVISOR_event_channel_op(EVTCHNOP_set_priority,
					   &set_priority);
}