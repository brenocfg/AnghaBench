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
struct urb {TYPE_2__* ep; } ;
struct list_head {int dummy; } ;
struct fotg210_qh {scalar_t__ qh_state; } ;
struct fotg210_hcd {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int bEndpointAddress; } ;
struct TYPE_4__ {int /*<<< orphan*/  hcpriv; TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (int /*<<< orphan*/ ) ; 
 scalar_t__ QH_STATE_IDLE ; 
 int /*<<< orphan*/  fotg210_to_hcd (struct fotg210_hcd*) ; 
 scalar_t__ likely (int) ; 
 struct fotg210_qh* qh_append_tds (struct fotg210_hcd*,struct urb*,struct list_head*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_link_async (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  qtd_list_free (struct fotg210_hcd*,struct urb*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 

__attribute__((used)) static int submit_async(struct fotg210_hcd *fotg210, struct urb *urb,
		struct list_head *qtd_list, gfp_t mem_flags)
{
	int epnum;
	unsigned long flags;
	struct fotg210_qh *qh = NULL;
	int rc;

	epnum = urb->ep->desc.bEndpointAddress;

#ifdef FOTG210_URB_TRACE
	{
		struct fotg210_qtd *qtd;

		qtd = list_entry(qtd_list->next, struct fotg210_qtd, qtd_list);
		fotg210_dbg(fotg210,
				"%s %s urb %p ep%d%s len %d, qtd %p [qh %p]\n",
				__func__, urb->dev->devpath, urb,
				epnum & 0x0f, (epnum & USB_DIR_IN)
					? "in" : "out",
				urb->transfer_buffer_length,
				qtd, urb->ep->hcpriv);
	}
#endif

	spin_lock_irqsave(&fotg210->lock, flags);
	if (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) {
		rc = -ESHUTDOWN;
		goto done;
	}
	rc = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	if (unlikely(rc))
		goto done;

	qh = qh_append_tds(fotg210, urb, qtd_list, epnum, &urb->ep->hcpriv);
	if (unlikely(qh == NULL)) {
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
		rc = -ENOMEM;
		goto done;
	}

	/* Control/bulk operations through TTs don't need scheduling,
	 * the HC and TT handle it when the TT has a buffer ready.
	 */
	if (likely(qh->qh_state == QH_STATE_IDLE))
		qh_link_async(fotg210, qh);
done:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	if (unlikely(qh == NULL))
		qtd_list_free(fotg210, urb, qtd_list);
	return rc;
}