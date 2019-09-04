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
struct usb_hcd {int dummy; } ;
struct urb {scalar_t__ hcpriv; int /*<<< orphan*/  pipe; } ;
struct fotg210_qh {int /*<<< orphan*/  qh_state; } ;
struct fotg210_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  PIPE_INTERRUPT 134 
#define  PIPE_ISOCHRONOUS 133 
#define  QH_STATE_COMPLETING 132 
#define  QH_STATE_IDLE 131 
#define  QH_STATE_LINKED 130 
#define  QH_STATE_UNLINK 129 
#define  QH_STATE_UNLINK_WAIT 128 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,struct fotg210_qh*,int /*<<< orphan*/ ) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  qh_completions (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_unlink_async (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  start_unlink_intr (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fotg210_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	struct fotg210_qh *qh;
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&fotg210->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto done;

	switch (usb_pipetype(urb->pipe)) {
	/* case PIPE_CONTROL: */
	/* case PIPE_BULK:*/
	default:
		qh = (struct fotg210_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
		case QH_STATE_COMPLETING:
			start_unlink_async(fotg210, qh);
			break;
		case QH_STATE_UNLINK:
		case QH_STATE_UNLINK_WAIT:
			/* already started */
			break;
		case QH_STATE_IDLE:
			/* QH might be waiting for a Clear-TT-Buffer */
			qh_completions(fotg210, qh);
			break;
		}
		break;

	case PIPE_INTERRUPT:
		qh = (struct fotg210_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
		case QH_STATE_COMPLETING:
			start_unlink_intr(fotg210, qh);
			break;
		case QH_STATE_IDLE:
			qh_completions(fotg210, qh);
			break;
		default:
			fotg210_dbg(fotg210, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			goto done;
		}
		break;

	case PIPE_ISOCHRONOUS:
		/* itd... */

		/* wait till next completion, do it then. */
		/* completion irqs can wait up to 1024 msec, */
		break;
	}
done:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	return rc;
}