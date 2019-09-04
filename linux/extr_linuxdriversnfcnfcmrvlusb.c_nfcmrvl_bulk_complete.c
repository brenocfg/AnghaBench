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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  status; struct nfcmrvl_usb_drv_data* context; } ;
struct sk_buff {int dummy; } ;
struct nfcmrvl_usb_drv_data {TYPE_1__* udev; int /*<<< orphan*/  bulk_anchor; int /*<<< orphan*/  flags; TYPE_2__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NFCMRVL_NCI_RUNNING ; 
 int /*<<< orphan*/  NFCMRVL_USB_BULK_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nci_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ nfcmrvl_nci_recv_frame (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (TYPE_1__*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void nfcmrvl_bulk_complete(struct urb *urb)
{
	struct nfcmrvl_usb_drv_data *drv_data = urb->context;
	struct sk_buff *skb;
	int err;

	dev_dbg(&drv_data->udev->dev, "urb %p status %d count %d\n",
		urb, urb->status, urb->actual_length);

	if (!test_bit(NFCMRVL_NCI_RUNNING, &drv_data->flags))
		return;

	if (!urb->status) {
		skb = nci_skb_alloc(drv_data->priv->ndev, urb->actual_length,
				    GFP_ATOMIC);
		if (!skb) {
			nfc_err(&drv_data->udev->dev, "failed to alloc mem\n");
		} else {
			skb_put_data(skb, urb->transfer_buffer,
				     urb->actual_length);
			if (nfcmrvl_nci_recv_frame(drv_data->priv, skb) < 0)
				nfc_err(&drv_data->udev->dev,
					"corrupted Rx packet\n");
		}
	}

	if (!test_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags))
		return;

	usb_anchor_urb(urb, &drv_data->bulk_anchor);
	usb_mark_last_busy(drv_data->udev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		/* -EPERM: urb is being killed;
		 * -ENODEV: device got disconnected
		 */
		if (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p failed to resubmit (%d)\n", urb, -err);
		usb_unanchor_urb(urb);
	}
}