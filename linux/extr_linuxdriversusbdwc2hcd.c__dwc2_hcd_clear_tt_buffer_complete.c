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
struct usb_host_endpoint {struct dwc2_qh* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct dwc2_qh {scalar_t__ tt_buffer_dirty; } ;
struct TYPE_3__ {scalar_t__ port_connect_status; } ;
struct TYPE_4__ {TYPE_1__ b; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; TYPE_2__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_TRANSACTION_ALL ; 
 int /*<<< orphan*/  dwc2_hcd_queue_transactions (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _dwc2_hcd_clear_tt_buffer_complete(struct usb_hcd *hcd,
					       struct usb_host_endpoint *ep)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	struct dwc2_qh *qh;
	unsigned long flags;

	qh = ep->hcpriv;
	if (!qh)
		return;

	spin_lock_irqsave(&hsotg->lock, flags);
	qh->tt_buffer_dirty = 0;

	if (hsotg->flags.b.port_connect_status)
		dwc2_hcd_queue_transactions(hsotg, DWC2_TRANSACTION_ALL);

	spin_unlock_irqrestore(&hsotg->lock, flags);
}