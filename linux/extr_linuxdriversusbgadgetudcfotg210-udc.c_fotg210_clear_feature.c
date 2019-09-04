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
struct usb_ctrlrequest {size_t wIndex; int bRequestType; } ;
struct fotg210_udc {struct fotg210_ep** ep; } ;
struct fotg210_ep {int /*<<< orphan*/  ep; int /*<<< orphan*/  stall; int /*<<< orphan*/  wedged; } ;

/* Variables and functions */
 size_t USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  fotg210_request_error (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_cxdone (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_halt_and_wedge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fotg210_clear_feature(struct fotg210_udc *fotg210,
				struct usb_ctrlrequest *ctrl)
{
	struct fotg210_ep *ep =
		fotg210->ep[ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK];

	switch (ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		fotg210_set_cxdone(fotg210);
		break;
	case USB_RECIP_INTERFACE:
		fotg210_set_cxdone(fotg210);
		break;
	case USB_RECIP_ENDPOINT:
		if (ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK) {
			if (ep->wedged) {
				fotg210_set_cxdone(fotg210);
				break;
			}
			if (ep->stall)
				fotg210_set_halt_and_wedge(&ep->ep, 0, 0);
		}
		fotg210_set_cxdone(fotg210);
		break;
	default:
		fotg210_request_error(fotg210);
		break;
	}
}