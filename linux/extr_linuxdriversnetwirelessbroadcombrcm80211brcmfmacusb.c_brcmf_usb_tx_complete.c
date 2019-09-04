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
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct brcmf_usbreq {int /*<<< orphan*/ * skb; struct brcmf_usbdev_info* devinfo; } ;
struct brcmf_usbdev_info {scalar_t__ tx_freecount; scalar_t__ tx_high_watermark; int tx_flowblock; int /*<<< orphan*/  tx_flowblock_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_freeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_txcomplete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_txflowblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmf_usb_del_fromq (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 
 int /*<<< orphan*/  brcmf_usb_enq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,struct brcmf_usbreq*,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void brcmf_usb_tx_complete(struct urb *urb)
{
	struct brcmf_usbreq *req = (struct brcmf_usbreq *)urb->context;
	struct brcmf_usbdev_info *devinfo = req->devinfo;
	unsigned long flags;

	brcmf_dbg(USB, "Enter, urb->status=%d, skb=%p\n", urb->status,
		  req->skb);
	brcmf_usb_del_fromq(devinfo, req);

	brcmf_proto_bcdc_txcomplete(devinfo->dev, req->skb, urb->status == 0);
	req->skb = NULL;
	brcmf_usb_enq(devinfo, &devinfo->tx_freeq, req, &devinfo->tx_freecount);
	spin_lock_irqsave(&devinfo->tx_flowblock_lock, flags);
	if (devinfo->tx_freecount > devinfo->tx_high_watermark &&
		devinfo->tx_flowblock) {
		brcmf_proto_bcdc_txflowblock(devinfo->dev, false);
		devinfo->tx_flowblock = false;
	}
	spin_unlock_irqrestore(&devinfo->tx_flowblock_lock, flags);
}