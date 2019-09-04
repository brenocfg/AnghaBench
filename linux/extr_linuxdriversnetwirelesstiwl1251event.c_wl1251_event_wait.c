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
typedef  int u32 ;
struct wl1251 {int /*<<< orphan*/ * mbox_ptr; } ;
typedef  int /*<<< orphan*/  events_vector ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wl1251_mem_read (struct wl1251*,int /*<<< orphan*/ ,int*,int) ; 

int wl1251_event_wait(struct wl1251 *wl, u32 mask, int timeout_ms)
{
	u32 events_vector, event;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(timeout_ms);

	do {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;

		msleep(1);

		/* read from both event fields */
		wl1251_mem_read(wl, wl->mbox_ptr[0], &events_vector,
				sizeof(events_vector));
		event = events_vector & mask;
		wl1251_mem_read(wl, wl->mbox_ptr[1], &events_vector,
				sizeof(events_vector));
		event |= events_vector & mask;
	} while (!event);

	return 0;
}