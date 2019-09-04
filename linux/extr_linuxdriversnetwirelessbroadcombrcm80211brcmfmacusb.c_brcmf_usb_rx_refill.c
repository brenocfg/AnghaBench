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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct brcmf_usbreq {struct sk_buff* skb; int /*<<< orphan*/  urb; struct brcmf_usbdev_info* devinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mtu; } ;
struct brcmf_usbdev_info {int /*<<< orphan*/  rx_freeq; int /*<<< orphan*/  rx_postq; int /*<<< orphan*/  rx_pipe; int /*<<< orphan*/  usbdev; TYPE_1__ bus_pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  brcmf_usb_del_fromq (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 
 int /*<<< orphan*/  brcmf_usb_enq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,struct brcmf_usbreq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_usb_rx_complete ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_usbreq*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_usb_rx_refill(struct brcmf_usbdev_info *devinfo,
				struct brcmf_usbreq  *req)
{
	struct sk_buff *skb;
	int ret;

	if (!req || !devinfo)
		return;

	skb = dev_alloc_skb(devinfo->bus_pub.bus_mtu);
	if (!skb) {
		brcmf_usb_enq(devinfo, &devinfo->rx_freeq, req, NULL);
		return;
	}
	req->skb = skb;

	usb_fill_bulk_urb(req->urb, devinfo->usbdev, devinfo->rx_pipe,
			  skb->data, skb_tailroom(skb), brcmf_usb_rx_complete,
			  req);
	req->devinfo = devinfo;
	brcmf_usb_enq(devinfo, &devinfo->rx_postq, req, NULL);

	ret = usb_submit_urb(req->urb, GFP_ATOMIC);
	if (ret) {
		brcmf_usb_del_fromq(devinfo, req);
		brcmu_pkt_buf_free_skb(req->skb);
		req->skb = NULL;
		brcmf_usb_enq(devinfo, &devinfo->rx_freeq, req, NULL);
	}
	return;
}