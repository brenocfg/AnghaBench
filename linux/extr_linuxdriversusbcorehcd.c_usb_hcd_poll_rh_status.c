#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  rh_timer; struct urb* status_urb; scalar_t__ uses_new_polling; int /*<<< orphan*/  flags; TYPE_1__* driver; int /*<<< orphan*/  rh_pollable; } ;
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; } ;
struct TYPE_2__ {int (* hub_status_data ) (struct usb_hcd*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_POLL_PENDING ; 
 int HCD_POLL_RH (struct usb_hcd*) ; 
 int HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcd_root_hub_lock ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct usb_hcd*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 

void usb_hcd_poll_rh_status(struct usb_hcd *hcd)
{
	struct urb	*urb;
	int		length;
	unsigned long	flags;
	char		buffer[6];	/* Any root hubs with > 31 ports? */

	if (unlikely(!hcd->rh_pollable))
		return;
	if (!hcd->uses_new_polling && !hcd->status_urb)
		return;

	length = hcd->driver->hub_status_data(hcd, buffer);
	if (length > 0) {

		/* try to complete the status urb */
		spin_lock_irqsave(&hcd_root_hub_lock, flags);
		urb = hcd->status_urb;
		if (urb) {
			clear_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
			hcd->status_urb = NULL;
			urb->actual_length = length;
			memcpy(urb->transfer_buffer, buffer, length);

			usb_hcd_unlink_urb_from_ep(hcd, urb);
			usb_hcd_giveback_urb(hcd, urb, 0);
		} else {
			length = 0;
			set_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
		}
		spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	}

	/* The USB 2.0 spec says 256 ms.  This is close enough and won't
	 * exceed that limit if HZ is 100. The math is more clunky than
	 * maybe expected, this is to make sure that all timers for USB devices
	 * fire at the same time to give the CPU a break in between */
	if (hcd->uses_new_polling ? HCD_POLL_RH(hcd) :
			(length == 0 && hcd->status_urb != NULL))
		mod_timer (&hcd->rh_timer, (jiffies/(HZ/4) + 1) * (HZ/4));
}