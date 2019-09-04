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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int bRequestType; int wIndex; } ;
struct xusb_udc {int (* read_fn ) (scalar_t__) ;int /*<<< orphan*/  dev; TYPE_1__ setup; scalar_t__ addr; struct xusb_ep* ep; int /*<<< orphan*/  remote_wkp; struct xusb_req* req; } ;
struct TYPE_4__ {int length; scalar_t__ buf; } ;
struct xusb_req {TYPE_2__ usb_req; } ;
struct xusb_ep {int /*<<< orphan*/  is_in; scalar_t__ offset; } ;

/* Variables and functions */
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_DEVICE_SELF_POWERED ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int XUSB_EP_CFG_STALL_MASK ; 
 int __xudc_ep0_queue (struct xusb_ep*,struct xusb_req*) ; 
 int cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  xudc_ep0_stall (struct xusb_udc*) ; 

__attribute__((used)) static void xudc_getstatus(struct xusb_udc *udc)
{
	struct xusb_ep *ep0	= &udc->ep[0];
	struct xusb_req *req	= udc->req;
	struct xusb_ep *target_ep;
	u16 status = 0;
	u32 epcfgreg;
	int epnum;
	u32 halt;
	int ret;

	switch (udc->setup.bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		/* Get device status */
		status = 1 << USB_DEVICE_SELF_POWERED;
		if (udc->remote_wkp)
			status |= (1 << USB_DEVICE_REMOTE_WAKEUP);
		break;
	case USB_RECIP_INTERFACE:
		break;
	case USB_RECIP_ENDPOINT:
		epnum = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
		target_ep = &udc->ep[epnum];
		epcfgreg = udc->read_fn(udc->addr + target_ep->offset);
		halt = epcfgreg & XUSB_EP_CFG_STALL_MASK;
		if (udc->setup.wIndex & USB_DIR_IN) {
			if (!target_ep->is_in)
				goto stall;
		} else {
			if (target_ep->is_in)
				goto stall;
		}
		if (halt)
			status = 1 << USB_ENDPOINT_HALT;
		break;
	default:
		goto stall;
	}

	req->usb_req.length = 2;
	*(u16 *)req->usb_req.buf = cpu_to_le16(status);
	ret = __xudc_ep0_queue(ep0, req);
	if (ret == 0)
		return;
stall:
	dev_err(udc->dev, "Can't respond to getstatus request\n");
	xudc_ep0_stall(udc);
}