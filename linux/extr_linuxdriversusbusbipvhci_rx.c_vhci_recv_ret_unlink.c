#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vhci_unlink {int /*<<< orphan*/  unlink_seqnum; } ;
struct vhci_hcd {struct vhci* vhci; } ;
struct vhci_device {int /*<<< orphan*/  priv_lock; } ;
struct vhci {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_2__ ret_unlink; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_3__ u; TYPE_1__ base; } ;
struct urb {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 struct vhci_unlink* dequeue_pending_unlink (struct vhci_device*,struct usbip_header*) ; 
 int /*<<< orphan*/  kfree (struct vhci_unlink*) ; 
 struct urb* pickup_urb_and_free_priv (struct vhci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dump_header (struct usbip_header*) ; 
 struct vhci_hcd* vdev_to_vhci_hcd (struct vhci_device*) ; 
 int /*<<< orphan*/  vhci_hcd_to_hcd (struct vhci_hcd*) ; 

__attribute__((used)) static void vhci_recv_ret_unlink(struct vhci_device *vdev,
				 struct usbip_header *pdu)
{
	struct vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	struct vhci *vhci = vhci_hcd->vhci;
	struct vhci_unlink *unlink;
	struct urb *urb;
	unsigned long flags;

	usbip_dump_header(pdu);

	unlink = dequeue_pending_unlink(vdev, pdu);
	if (!unlink) {
		pr_info("cannot find the pending unlink %u\n",
			pdu->base.seqnum);
		return;
	}

	spin_lock_irqsave(&vdev->priv_lock, flags);
	urb = pickup_urb_and_free_priv(vdev, unlink->unlink_seqnum);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	if (!urb) {
		/*
		 * I get the result of a unlink request. But, it seems that I
		 * already received the result of its submit result and gave
		 * back the URB.
		 */
		pr_info("the urb (seqnum %d) was already given back\n",
			pdu->base.seqnum);
	} else {
		usbip_dbg_vhci_rx("now giveback urb %d\n", pdu->base.seqnum);

		/* If unlink is successful, status is -ECONNRESET */
		urb->status = pdu->u.ret_unlink.status;
		pr_info("urb->status %d\n", urb->status);

		spin_lock_irqsave(&vhci->lock, flags);
		usb_hcd_unlink_urb_from_ep(vhci_hcd_to_hcd(vhci_hcd), urb);
		spin_unlock_irqrestore(&vhci->lock, flags);

		usb_hcd_giveback_urb(vhci_hcd_to_hcd(vhci_hcd), urb, urb->status);
	}

	kfree(unlink);
}