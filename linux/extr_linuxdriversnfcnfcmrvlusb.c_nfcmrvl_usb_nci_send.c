#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  setup_packet; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfcmrvl_usb_drv_data {TYPE_2__* udev; int /*<<< orphan*/  tx_anchor; int /*<<< orphan*/  waker; int /*<<< orphan*/  deferred; TYPE_1__* bulk_tx_ep; } ;
struct nfcmrvl_private {struct nfcmrvl_usb_drv_data* drv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,struct urb*,int) ; 
 int nfcmrvl_inc_tx (struct nfcmrvl_usb_drv_data*) ; 
 int /*<<< orphan*/  nfcmrvl_tx_complete ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_2__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (TYPE_2__*) ; 
 unsigned int usb_sndbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int nfcmrvl_usb_nci_send(struct nfcmrvl_private *priv,
				struct sk_buff *skb)
{
	struct nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	struct urb *urb;
	unsigned int pipe;
	int err;

	if (!drv_data->bulk_tx_ep)
		return -ENODEV;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		return -ENOMEM;

	pipe = usb_sndbulkpipe(drv_data->udev,
				drv_data->bulk_tx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, drv_data->udev, pipe, skb->data, skb->len,
			  nfcmrvl_tx_complete, skb);

	err = nfcmrvl_inc_tx(drv_data);
	if (err) {
		usb_anchor_urb(urb, &drv_data->deferred);
		schedule_work(&drv_data->waker);
		err = 0;
		goto done;
	}

	usb_anchor_urb(urb, &drv_data->tx_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		if (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p submission failed (%d)\n", urb, -err);
		kfree(urb->setup_packet);
		usb_unanchor_urb(urb);
	} else {
		usb_mark_last_busy(drv_data->udev);
	}

done:
	usb_free_urb(urb);
	return err;
}