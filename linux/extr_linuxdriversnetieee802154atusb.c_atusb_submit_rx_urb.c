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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct urb {struct sk_buff* context; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct atusb {int /*<<< orphan*/  rx_urbs; struct usb_device* usb_dev; } ;
typedef  struct atusb* SKB_ATUSB ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_RX_XFER ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atusb_in ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int atusb_submit_rx_urb(struct atusb *atusb, struct urb *urb)
{
	struct usb_device *usb_dev = atusb->usb_dev;
	struct sk_buff *skb = urb->context;
	int ret;

	if (!skb) {
		skb = alloc_skb(MAX_RX_XFER, GFP_KERNEL);
		if (!skb) {
			dev_warn_ratelimited(&usb_dev->dev,
					     "atusb_in: can't allocate skb\n");
			return -ENOMEM;
		}
		skb_put(skb, MAX_RX_XFER);
		SKB_ATUSB(skb) = atusb;
	}

	usb_fill_bulk_urb(urb, usb_dev, usb_rcvbulkpipe(usb_dev, 1),
			  skb->data, MAX_RX_XFER, atusb_in, skb);
	usb_anchor_urb(urb, &atusb->rx_urbs);

	ret = usb_submit_urb(urb, GFP_KERNEL);
	if (ret) {
		usb_unanchor_urb(urb);
		kfree_skb(skb);
		urb->context = NULL;
	}
	return ret;
}