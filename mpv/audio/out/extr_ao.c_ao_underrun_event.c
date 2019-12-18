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
struct ao {int /*<<< orphan*/  events_; } ;

/* Variables and functions */
 int AO_EVENT_UNDERRUN ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 int /*<<< orphan*/  ao_add_events (struct ao*,int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 

void ao_underrun_event(struct ao *ao)
{
    // Racy check, but it's just for the message.
    if (!(atomic_load(&ao->events_) & AO_EVENT_UNDERRUN))
        MP_WARN(ao, "Device underrun detected.\n");
    ao_add_events(ao, AO_EVENT_UNDERRUN);
}