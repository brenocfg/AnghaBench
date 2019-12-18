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
struct snd_usb_endpoint {int /*<<< orphan*/ * prepare_data_urb; int /*<<< orphan*/ * retire_data_urb; int /*<<< orphan*/ * sync_slave; int /*<<< orphan*/ * data_subs; int /*<<< orphan*/  flags; int /*<<< orphan*/  ep_num; int /*<<< orphan*/  chip; int /*<<< orphan*/  nurbs; int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FLAG_STOPPING ; 
 int bitmap_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usb_audio_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_clear_urbs(struct snd_usb_endpoint *ep)
{
	unsigned long end_time = jiffies + msecs_to_jiffies(1000);
	int alive;

	do {
		alive = bitmap_weight(&ep->active_mask, ep->nurbs);
		if (!alive)
			break;

		schedule_timeout_uninterruptible(1);
	} while (time_before(jiffies, end_time));

	if (alive)
		usb_audio_err(ep->chip,
			"timeout: still %d active urbs on EP #%x\n",
			alive, ep->ep_num);
	clear_bit(EP_FLAG_STOPPING, &ep->flags);

	ep->data_subs = NULL;
	ep->sync_slave = NULL;
	ep->retire_data_urb = NULL;
	ep->prepare_data_urb = NULL;

	return 0;
}