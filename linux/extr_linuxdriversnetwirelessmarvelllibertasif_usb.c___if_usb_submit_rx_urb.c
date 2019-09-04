#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct if_usb_card {TYPE_1__* udev; struct sk_buff* rx_skb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  ep_in; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPFIELD_ALIGN_OFFSET ; 
 int /*<<< orphan*/  MRVDRV_ETH_RX_PACKET_BUFFER_SIZE ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lbs_deb_usb2 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void (*) (struct urb*),struct if_usb_card*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __if_usb_submit_rx_urb(struct if_usb_card *cardp,
				  void (*callbackfn)(struct urb *urb))
{
	struct sk_buff *skb;
	int ret = -1;

	if (!(skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE))) {
		pr_err("No free skb\n");
		goto rx_ret;
	}

	cardp->rx_skb = skb;

	/* Fill the receive configuration URB and initialise the Rx call back */
	usb_fill_bulk_urb(cardp->rx_urb, cardp->udev,
			  usb_rcvbulkpipe(cardp->udev, cardp->ep_in),
			  skb->data + IPFIELD_ALIGN_OFFSET,
			  MRVDRV_ETH_RX_PACKET_BUFFER_SIZE, callbackfn,
			  cardp);

	lbs_deb_usb2(&cardp->udev->dev, "Pointer for rx_urb %p\n", cardp->rx_urb);
	if ((ret = usb_submit_urb(cardp->rx_urb, GFP_ATOMIC))) {
		lbs_deb_usbd(&cardp->udev->dev, "Submit Rx URB failed: %d\n", ret);
		kfree_skb(skb);
		cardp->rx_skb = NULL;
		ret = -1;
	} else {
		lbs_deb_usb2(&cardp->udev->dev, "Submit Rx URB success\n");
		ret = 0;
	}

rx_ret:
	return ret;
}