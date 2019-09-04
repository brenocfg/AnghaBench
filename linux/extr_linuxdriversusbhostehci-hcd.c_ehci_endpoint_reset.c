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
struct usb_host_endpoint {struct ehci_qh* hcpriv; int /*<<< orphan*/  desc; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;
struct ehci_qh {int /*<<< orphan*/  unlink_reason; TYPE_1__ ps; int /*<<< orphan*/  qtd_list; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QH_UNLINK_REQUESTED ; 
 int USB_ENDPOINT_XFER_BULK ; 
 int USB_ENDPOINT_XFER_INT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  start_unlink_intr (struct ehci_hcd*,struct ehci_qh*) ; 
 int usb_endpoint_dir_out (int /*<<< orphan*/ *) ; 
 int usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int usb_endpoint_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_settoggle (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehci_endpoint_reset(struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	struct ehci_qh		*qh;
	int			eptype = usb_endpoint_type(&ep->desc);
	int			epnum = usb_endpoint_num(&ep->desc);
	int			is_out = usb_endpoint_dir_out(&ep->desc);
	unsigned long		flags;

	if (eptype != USB_ENDPOINT_XFER_BULK && eptype != USB_ENDPOINT_XFER_INT)
		return;

	spin_lock_irqsave(&ehci->lock, flags);
	qh = ep->hcpriv;

	/* For Bulk and Interrupt endpoints we maintain the toggle state
	 * in the hardware; the toggle bits in udev aren't used at all.
	 * When an endpoint is reset by usb_clear_halt() we must reset
	 * the toggle bit in the QH.
	 */
	if (qh) {
		if (!list_empty(&qh->qtd_list)) {
			WARN_ONCE(1, "clear_halt for a busy endpoint\n");
		} else {
			/* The toggle value in the QH can't be updated
			 * while the QH is active.  Unlink it now;
			 * re-linking will call qh_refresh().
			 */
			usb_settoggle(qh->ps.udev, epnum, is_out, 0);
			qh->unlink_reason |= QH_UNLINK_REQUESTED;
			if (eptype == USB_ENDPOINT_XFER_BULK)
				start_unlink_async(ehci, qh);
			else
				start_unlink_intr(ehci, qh);
		}
	}
	spin_unlock_irqrestore(&ehci->lock, flags);
}