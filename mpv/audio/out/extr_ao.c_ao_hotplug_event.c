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
struct ao {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_EVENT_HOTPLUG ; 
 int /*<<< orphan*/  ao_add_events (struct ao*,int /*<<< orphan*/ ) ; 

void ao_hotplug_event(struct ao *ao)
{
    ao_add_events(ao, AO_EVENT_HOTPLUG);
}