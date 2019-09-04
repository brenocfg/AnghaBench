#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {scalar_t__ expires; } ;
struct xhci_virt_ep {int ep_state; TYPE_5__ stop_cmd_timer; int /*<<< orphan*/  cancelled_td_list; } ;
struct xhci_virt_device {struct xhci_virt_ep* eps; } ;
struct xhci_td {int /*<<< orphan*/  cancelled_td_list; int /*<<< orphan*/  first_trb; int /*<<< orphan*/  start_seg; int /*<<< orphan*/  td_list; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int xhc_state; int /*<<< orphan*/  lock; TYPE_1__* op_regs; struct xhci_virt_device** devs; } ;
struct xhci_command {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct urb_priv {int num_tds_done; int num_tds; struct xhci_td* td; } ;
struct urb {TYPE_3__* dev; TYPE_2__* ep; struct urb_priv* hcpriv; } ;
struct TYPE_9__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_8__ {size_t slot_id; int /*<<< orphan*/  devpath; } ;
struct TYPE_7__ {TYPE_4__ desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EP_STOP_CMD_PENDING ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int XHCI_STATE_DYING ; 
 int XHCI_STATE_HALTED ; 
 int XHCI_STOP_EP_CMD_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_5__*) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  td_on_ring (struct xhci_td*,struct xhci_ring*) ; 
 int /*<<< orphan*/  trace_xhci_dbg_cancel_urb ; 
 int /*<<< orphan*/  trace_xhci_urb_dequeue (struct urb*) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 unsigned int xhci_get_endpoint_index (TYPE_4__*) ; 
 int /*<<< orphan*/  xhci_hc_died (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_queue_stop_endpoint (struct xhci_hcd*,struct xhci_command*,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 scalar_t__ xhci_trb_virt_to_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_urb_free_priv (struct urb_priv*) ; 
 struct xhci_ring* xhci_urb_to_transfer_ring (struct xhci_hcd*,struct urb*) ; 

__attribute__((used)) static int xhci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	unsigned long flags;
	int ret, i;
	u32 temp;
	struct xhci_hcd *xhci;
	struct urb_priv	*urb_priv;
	struct xhci_td *td;
	unsigned int ep_index;
	struct xhci_ring *ep_ring;
	struct xhci_virt_ep *ep;
	struct xhci_command *command;
	struct xhci_virt_device *vdev;

	xhci = hcd_to_xhci(hcd);
	spin_lock_irqsave(&xhci->lock, flags);

	trace_xhci_urb_dequeue(urb);

	/* Make sure the URB hasn't completed or been unlinked already */
	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (ret)
		goto done;

	/* give back URB now if we can't queue it for cancel */
	vdev = xhci->devs[urb->dev->slot_id];
	urb_priv = urb->hcpriv;
	if (!vdev || !urb_priv)
		goto err_giveback;

	ep_index = xhci_get_endpoint_index(&urb->ep->desc);
	ep = &vdev->eps[ep_index];
	ep_ring = xhci_urb_to_transfer_ring(xhci, urb);
	if (!ep || !ep_ring)
		goto err_giveback;

	/* If xHC is dead take it down and return ALL URBs in xhci_hc_died() */
	temp = readl(&xhci->op_regs->status);
	if (temp == ~(u32)0 || xhci->xhc_state & XHCI_STATE_DYING) {
		xhci_hc_died(xhci);
		goto done;
	}

	/*
	 * check ring is not re-allocated since URB was enqueued. If it is, then
	 * make sure none of the ring related pointers in this URB private data
	 * are touched, such as td_list, otherwise we overwrite freed data
	 */
	if (!td_on_ring(&urb_priv->td[0], ep_ring)) {
		xhci_err(xhci, "Canceled URB td not found on endpoint ring");
		for (i = urb_priv->num_tds_done; i < urb_priv->num_tds; i++) {
			td = &urb_priv->td[i];
			if (!list_empty(&td->cancelled_td_list))
				list_del_init(&td->cancelled_td_list);
		}
		goto err_giveback;
	}

	if (xhci->xhc_state & XHCI_STATE_HALTED) {
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"HC halted, freeing TD manually.");
		for (i = urb_priv->num_tds_done;
		     i < urb_priv->num_tds;
		     i++) {
			td = &urb_priv->td[i];
			if (!list_empty(&td->td_list))
				list_del_init(&td->td_list);
			if (!list_empty(&td->cancelled_td_list))
				list_del_init(&td->cancelled_td_list);
		}
		goto err_giveback;
	}

	i = urb_priv->num_tds_done;
	if (i < urb_priv->num_tds)
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"Cancel URB %p, dev %s, ep 0x%x, "
				"starting at offset 0x%llx",
				urb, urb->dev->devpath,
				urb->ep->desc.bEndpointAddress,
				(unsigned long long) xhci_trb_virt_to_dma(
					urb_priv->td[i].start_seg,
					urb_priv->td[i].first_trb));

	for (; i < urb_priv->num_tds; i++) {
		td = &urb_priv->td[i];
		list_add_tail(&td->cancelled_td_list, &ep->cancelled_td_list);
	}

	/* Queue a stop endpoint command, but only if this is
	 * the first cancellation to be handled.
	 */
	if (!(ep->ep_state & EP_STOP_CMD_PENDING)) {
		command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
		if (!command) {
			ret = -ENOMEM;
			goto done;
		}
		ep->ep_state |= EP_STOP_CMD_PENDING;
		ep->stop_cmd_timer.expires = jiffies +
			XHCI_STOP_EP_CMD_TIMEOUT * HZ;
		add_timer(&ep->stop_cmd_timer);
		xhci_queue_stop_endpoint(xhci, command, urb->dev->slot_id,
					 ep_index, 0);
		xhci_ring_cmd_db(xhci);
	}
done:
	spin_unlock_irqrestore(&xhci->lock, flags);
	return ret;

err_giveback:
	if (urb_priv)
		xhci_urb_free_priv(urb_priv);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	spin_unlock_irqrestore(&xhci->lock, flags);
	usb_hcd_giveback_urb(hcd, urb, -ESHUTDOWN);
	return ret;
}