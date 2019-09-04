#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_request {int length; scalar_t__ zero; } ;
struct usb_function {struct usb_configuration* config; } ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct usb_configuration {TYPE_2__* cdev; } ;
struct TYPE_5__ {TYPE_1__* gadget; struct usb_request* req; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ERROR (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_COMP_EP0_BUFSIZ ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  VDBG (TYPE_2__*,char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_ep_queue (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sourcesink_setup(struct usb_function *f,
		const struct usb_ctrlrequest *ctrl)
{
	struct usb_configuration        *c = f->config;
	struct usb_request	*req = c->cdev->req;
	int			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	req->length = USB_COMP_EP0_BUFSIZ;

	/* composite driver infrastructure handles everything except
	 * the two control test requests.
	 */
	switch (ctrl->bRequest) {

	/*
	 * These are the same vendor-specific requests supported by
	 * Intel's USB 2.0 compliance test devices.  We exceed that
	 * device spec by allowing multiple-packet requests.
	 *
	 * NOTE:  the Control-OUT data stays in req->buf ... better
	 * would be copying it into a scratch buffer, so that other
	 * requests may safely intervene.
	 */
	case 0x5b:	/* control WRITE test -- fill the buffer */
		if (ctrl->bRequestType != (USB_DIR_OUT|USB_TYPE_VENDOR))
			goto unknown;
		if (w_value || w_index)
			break;
		/* just read that many bytes into the buffer */
		if (w_length > req->length)
			break;
		value = w_length;
		break;
	case 0x5c:	/* control READ test -- return the buffer */
		if (ctrl->bRequestType != (USB_DIR_IN|USB_TYPE_VENDOR))
			goto unknown;
		if (w_value || w_index)
			break;
		/* expect those bytes are still in the buffer; send back */
		if (w_length > req->length)
			break;
		value = w_length;
		break;

	default:
unknown:
		VDBG(c->cdev,
			"unknown control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	}

	/* respond with data transfer or status phase? */
	if (value >= 0) {
		VDBG(c->cdev, "source/sink req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(c->cdev->gadget->ep0, req, GFP_ATOMIC);
		if (value < 0)
			ERROR(c->cdev, "source/sink response, err %d\n",
					value);
	}

	/* device either stalls (value < 0) or reports success */
	return value;
}