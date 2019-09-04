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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ bRequest; int bRequestType; size_t wIndex; int /*<<< orphan*/  wValue; } ;
struct xusb_udc {int remote_wkp; int (* read_fn ) (scalar_t__) ;int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__,int) ;TYPE_1__ setup; struct xusb_ep* ep; struct xusb_req* req; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct xusb_req {TYPE_2__ usb_req; } ;
struct xusb_ep {size_t is_in; scalar_t__ offset; } ;

/* Variables and functions */
#define  USB_DEVICE_REMOTE_WAKEUP 131 
#define  USB_DEVICE_TEST_MODE 130 
 size_t USB_ENDPOINT_DIR_MASK ; 
 size_t USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 129 
#define  USB_RECIP_ENDPOINT 128 
 scalar_t__ USB_REQ_SET_FEATURE ; 
 int XUSB_EP_CFG_DATA_TOGGLE_MASK ; 
 int XUSB_EP_CFG_STALL_MASK ; 
 int __xudc_ep0_queue (struct xusb_ep*,struct xusb_req*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xudc_ep0_stall (struct xusb_udc*) ; 

__attribute__((used)) static void xudc_set_clear_feature(struct xusb_udc *udc)
{
	struct xusb_ep *ep0	= &udc->ep[0];
	struct xusb_req *req	= udc->req;
	struct xusb_ep *target_ep;
	u8 endpoint;
	u8 outinbit;
	u32 epcfgreg;
	int flag = (udc->setup.bRequest == USB_REQ_SET_FEATURE ? 1 : 0);
	int ret;

	switch (udc->setup.bRequestType) {
	case USB_RECIP_DEVICE:
		switch (udc->setup.wValue) {
		case USB_DEVICE_TEST_MODE:
			/*
			 * The Test Mode will be executed
			 * after the status phase.
			 */
			break;
		case USB_DEVICE_REMOTE_WAKEUP:
			if (flag)
				udc->remote_wkp = 1;
			else
				udc->remote_wkp = 0;
			break;
		default:
			xudc_ep0_stall(udc);
			break;
		}
		break;
	case USB_RECIP_ENDPOINT:
		if (!udc->setup.wValue) {
			endpoint = udc->setup.wIndex & USB_ENDPOINT_NUMBER_MASK;
			target_ep = &udc->ep[endpoint];
			outinbit = udc->setup.wIndex & USB_ENDPOINT_DIR_MASK;
			outinbit = outinbit >> 7;

			/* Make sure direction matches.*/
			if (outinbit != target_ep->is_in) {
				xudc_ep0_stall(udc);
				return;
			}
			epcfgreg = udc->read_fn(udc->addr + target_ep->offset);
			if (!endpoint) {
				/* Clear the stall.*/
				epcfgreg &= ~XUSB_EP_CFG_STALL_MASK;
				udc->write_fn(udc->addr,
					      target_ep->offset, epcfgreg);
			} else {
				if (flag) {
					epcfgreg |= XUSB_EP_CFG_STALL_MASK;
					udc->write_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				} else {
					/* Unstall the endpoint.*/
					epcfgreg &= ~(XUSB_EP_CFG_STALL_MASK |
						XUSB_EP_CFG_DATA_TOGGLE_MASK);
					udc->write_fn(udc->addr,
						      target_ep->offset,
						      epcfgreg);
				}
			}
		}
		break;
	default:
		xudc_ep0_stall(udc);
		return;
	}

	req->usb_req.length = 0;
	ret = __xudc_ep0_queue(ep0, req);
	if (ret == 0)
		return;

	dev_err(udc->dev, "Can't respond to SET/CLEAR FEATURE\n");
	xudc_ep0_stall(udc);
}