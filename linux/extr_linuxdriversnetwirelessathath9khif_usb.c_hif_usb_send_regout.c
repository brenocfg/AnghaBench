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
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hif_device_usb {int /*<<< orphan*/  regout_submitted; int /*<<< orphan*/  udev; } ;
struct cmd_buf {struct hif_device_usb* hif_dev; struct sk_buff* skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_REG_OUT_PIPE ; 
 int /*<<< orphan*/  hif_usb_regout_cb ; 
 int /*<<< orphan*/  kfree (struct cmd_buf*) ; 
 struct cmd_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_buf*,int) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int hif_usb_send_regout(struct hif_device_usb *hif_dev,
			       struct sk_buff *skb)
{
	struct urb *urb;
	struct cmd_buf *cmd;
	int ret = 0;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (urb == NULL)
		return -ENOMEM;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	cmd->skb = skb;
	cmd->hif_dev = hif_dev;

	usb_fill_int_urb(urb, hif_dev->udev,
			 usb_sndintpipe(hif_dev->udev, USB_REG_OUT_PIPE),
			 skb->data, skb->len,
			 hif_usb_regout_cb, cmd, 1);

	usb_anchor_urb(urb, &hif_dev->regout_submitted);
	ret = usb_submit_urb(urb, GFP_KERNEL);
	if (ret) {
		usb_unanchor_urb(urb);
		kfree(cmd);
	}
	usb_free_urb(urb);

	return ret;
}