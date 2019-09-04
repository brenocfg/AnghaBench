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
struct wusbhc {int dummy; } ;
struct whc_qset {int remove; int reset; } ;
struct whc {int /*<<< orphan*/  lock; int /*<<< orphan*/  periodic_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  async_work; } ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; struct whc_qset* hcpriv; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_endpoint_xfer_bulk (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static void whc_endpoint_reset(struct usb_hcd *usb_hcd,
			       struct usb_host_endpoint *ep)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);
	struct whc_qset *qset;
	unsigned long flags;

	spin_lock_irqsave(&whc->lock, flags);

	qset = ep->hcpriv;
	if (qset) {
		qset->remove = 1;
		qset->reset = 1;

		if (usb_endpoint_xfer_bulk(&ep->desc)
		    || usb_endpoint_xfer_control(&ep->desc))
			queue_work(whc->workqueue, &whc->async_work);
		else
			queue_work(whc->workqueue, &whc->periodic_work);
	}

	spin_unlock_irqrestore(&whc->lock, flags);
}