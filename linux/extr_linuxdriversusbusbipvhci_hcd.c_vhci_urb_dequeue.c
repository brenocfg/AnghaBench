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
struct vhci_unlink {int seqnum; int /*<<< orphan*/  list; int /*<<< orphan*/  unlink_seqnum; } ;
struct vhci_priv {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  list; struct vhci_device* vdev; } ;
struct vhci_hcd {int /*<<< orphan*/  seqnum; struct vhci* vhci; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_socket; } ;
struct vhci_device {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  unlink_tx; TYPE_1__ ud; } ;
struct vhci {int /*<<< orphan*/  lock; } ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  status; struct vhci_priv* hcpriv; } ;

/* Variables and functions */
 int EIDRM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct vhci_hcd* hcd_to_vhci_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (struct vhci_priv*) ; 
 struct vhci_unlink* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	struct vhci *vhci = vhci_hcd->vhci;
	struct vhci_priv *priv;
	struct vhci_device *vdev;
	unsigned long flags;

	spin_lock_irqsave(&vhci->lock, flags);

	priv = urb->hcpriv;
	if (!priv) {
		/* URB was never linked! or will be soon given back by
		 * vhci_rx. */
		spin_unlock_irqrestore(&vhci->lock, flags);
		return -EIDRM;
	}

	{
		int ret = 0;

		ret = usb_hcd_check_unlink_urb(hcd, urb, status);
		if (ret) {
			spin_unlock_irqrestore(&vhci->lock, flags);
			return ret;
		}
	}

	 /* send unlink request here? */
	vdev = priv->vdev;

	if (!vdev->ud.tcp_socket) {
		/* tcp connection is closed */
		spin_lock(&vdev->priv_lock);

		list_del(&priv->list);
		kfree(priv);
		urb->hcpriv = NULL;

		spin_unlock(&vdev->priv_lock);

		/*
		 * If tcp connection is alive, we have sent CMD_UNLINK.
		 * vhci_rx will receive RET_UNLINK and give back the URB.
		 * Otherwise, we give back it here.
		 */
		usb_hcd_unlink_urb_from_ep(hcd, urb);

		spin_unlock_irqrestore(&vhci->lock, flags);
		usb_hcd_giveback_urb(hcd, urb, urb->status);
		spin_lock_irqsave(&vhci->lock, flags);

	} else {
		/* tcp connection is alive */
		struct vhci_unlink *unlink;

		spin_lock(&vdev->priv_lock);

		/* setup CMD_UNLINK pdu */
		unlink = kzalloc(sizeof(struct vhci_unlink), GFP_ATOMIC);
		if (!unlink) {
			spin_unlock(&vdev->priv_lock);
			spin_unlock_irqrestore(&vhci->lock, flags);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
			return -ENOMEM;
		}

		unlink->seqnum = atomic_inc_return(&vhci_hcd->seqnum);
		if (unlink->seqnum == 0xffff)
			pr_info("seqnum max\n");

		unlink->unlink_seqnum = priv->seqnum;

		/* send cmd_unlink and try to cancel the pending URB in the
		 * peer */
		list_add_tail(&unlink->list, &vdev->unlink_tx);
		wake_up(&vdev->waitq_tx);

		spin_unlock(&vdev->priv_lock);
	}

	spin_unlock_irqrestore(&vhci->lock, flags);

	usbip_dbg_vhci_hc("leave\n");
	return 0;
}