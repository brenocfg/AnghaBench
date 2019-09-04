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
struct zd_usb {int /*<<< orphan*/  submitted_cmds; struct urb* urb_async_waiting; } ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_INTERRUPT ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 

__attribute__((used)) static int zd_submit_waiting_urb(struct zd_usb *usb, bool last)
{
	int r = 0;
	struct urb *urb = usb->urb_async_waiting;

	if (!urb)
		return 0;

	usb->urb_async_waiting = NULL;

	if (!last)
		urb->transfer_flags |= URB_NO_INTERRUPT;

	usb_anchor_urb(urb, &usb->submitted_cmds);
	r = usb_submit_urb(urb, GFP_KERNEL);
	if (r) {
		usb_unanchor_urb(urb);
		dev_dbg_f(zd_usb_dev(usb),
			"error in usb_submit_urb(). Error number %d\n", r);
		goto error;
	}

	/* fall-through with r == 0 */
error:
	usb_free_urb(urb);
	return r;
}