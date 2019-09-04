#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct urb {TYPE_2__* ep; int /*<<< orphan*/  urb_list; scalar_t__ unlinked; TYPE_1__* dev; int /*<<< orphan*/  reject; } ;
struct TYPE_4__ {int /*<<< orphan*/  urb_list; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  can_submit; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENOENT ; 
 int EPERM ; 
 int ESHUTDOWN ; 
 scalar_t__ HCD_RH_RUNNING (struct usb_hcd*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcd_urb_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int usb_hcd_link_urb_to_ep(struct usb_hcd *hcd, struct urb *urb)
{
	int		rc = 0;

	spin_lock(&hcd_urb_list_lock);

	/* Check that the URB isn't being killed */
	if (unlikely(atomic_read(&urb->reject))) {
		rc = -EPERM;
		goto done;
	}

	if (unlikely(!urb->ep->enabled)) {
		rc = -ENOENT;
		goto done;
	}

	if (unlikely(!urb->dev->can_submit)) {
		rc = -EHOSTUNREACH;
		goto done;
	}

	/*
	 * Check the host controller's state and add the URB to the
	 * endpoint's queue.
	 */
	if (HCD_RH_RUNNING(hcd)) {
		urb->unlinked = 0;
		list_add_tail(&urb->urb_list, &urb->ep->urb_list);
	} else {
		rc = -ESHUTDOWN;
		goto done;
	}
 done:
	spin_unlock(&hcd_urb_list_lock);
	return rc;
}