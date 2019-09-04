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
struct event_mailbox {int /*<<< orphan*/  events_mask; int /*<<< orphan*/  events_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wl1251_event_mbox_dump(struct event_mailbox *mbox)
{
	wl1251_debug(DEBUG_EVENT, "MBOX DUMP:");
	wl1251_debug(DEBUG_EVENT, "\tvector: 0x%x", mbox->events_vector);
	wl1251_debug(DEBUG_EVENT, "\tmask: 0x%x", mbox->events_mask);
}