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
struct ef4_channel {int /*<<< orphan*/  eventq_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_event (struct ef4_channel*,int /*<<< orphan*/ ) ; 
 int ef4_event_present (int /*<<< orphan*/ ) ; 

bool ef4_nic_event_present(struct ef4_channel *channel)
{
	return ef4_event_present(ef4_event(channel, channel->eventq_read_ptr));
}