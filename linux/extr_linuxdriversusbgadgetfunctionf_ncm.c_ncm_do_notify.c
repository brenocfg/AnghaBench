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
struct usb_request {int length; struct usb_cdc_notification* buf; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct usb_cdc_notification {int bmRequestType; void* wIndex; void* wLength; void* wValue; int /*<<< orphan*/  bNotificationType; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_6__ {TYPE_2__ func; } ;
struct f_ncm {int notify_state; int ctrl_id; struct usb_request* notify_req; int /*<<< orphan*/  lock; int /*<<< orphan*/  notify; int /*<<< orphan*/  is_open; TYPE_3__ port; } ;
typedef  struct usb_cdc_notification __le32 ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  NCM_NOTIFY_CONNECT 130 
#define  NCM_NOTIFY_NONE 129 
#define  NCM_NOTIFY_SPEED 128 
 int NCM_STATUS_BYTECOUNT ; 
 int /*<<< orphan*/  USB_CDC_NOTIFY_NETWORK_CONNECTION ; 
 int /*<<< orphan*/  USB_CDC_NOTIFY_SPEED_CHANGE ; 
 void* cpu_to_le16 (int) ; 
 struct usb_cdc_notification cpu_to_le32 (int) ; 
 int ncm_bitrate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int usb_ep_queue (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ncm_do_notify(struct f_ncm *ncm)
{
	struct usb_request		*req = ncm->notify_req;
	struct usb_cdc_notification	*event;
	struct usb_composite_dev	*cdev = ncm->port.func.config->cdev;
	__le32				*data;
	int				status;

	/* notification already in flight? */
	if (!req)
		return;

	event = req->buf;
	switch (ncm->notify_state) {
	case NCM_NOTIFY_NONE:
		return;

	case NCM_NOTIFY_CONNECT:
		event->bNotificationType = USB_CDC_NOTIFY_NETWORK_CONNECTION;
		if (ncm->is_open)
			event->wValue = cpu_to_le16(1);
		else
			event->wValue = cpu_to_le16(0);
		event->wLength = 0;
		req->length = sizeof *event;

		DBG(cdev, "notify connect %s\n",
				ncm->is_open ? "true" : "false");
		ncm->notify_state = NCM_NOTIFY_NONE;
		break;

	case NCM_NOTIFY_SPEED:
		event->bNotificationType = USB_CDC_NOTIFY_SPEED_CHANGE;
		event->wValue = cpu_to_le16(0);
		event->wLength = cpu_to_le16(8);
		req->length = NCM_STATUS_BYTECOUNT;

		/* SPEED_CHANGE data is up/down speeds in bits/sec */
		data = req->buf + sizeof *event;
		data[0] = cpu_to_le32(ncm_bitrate(cdev->gadget));
		data[1] = data[0];

		DBG(cdev, "notify speed %d\n", ncm_bitrate(cdev->gadget));
		ncm->notify_state = NCM_NOTIFY_CONNECT;
		break;
	}
	event->bmRequestType = 0xA1;
	event->wIndex = cpu_to_le16(ncm->ctrl_id);

	ncm->notify_req = NULL;
	/*
	 * In double buffering if there is a space in FIFO,
	 * completion callback can be called right after the call,
	 * so unlocking
	 */
	spin_unlock(&ncm->lock);
	status = usb_ep_queue(ncm->notify, req, GFP_ATOMIC);
	spin_lock(&ncm->lock);
	if (status < 0) {
		ncm->notify_req = req;
		DBG(cdev, "notify --> %d\n", status);
	}
}