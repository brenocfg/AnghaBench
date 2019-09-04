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
typedef  size_t u8 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wIndex; } ;
struct fotg210_udc {int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 size_t USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  fotg210_request_error (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_cxdone (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_cxstall (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_epnstall (int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fotg210_set_feature(struct fotg210_udc *fotg210,
				struct usb_ctrlrequest *ctrl)
{
	switch (ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		fotg210_set_cxdone(fotg210);
		break;
	case USB_RECIP_INTERFACE:
		fotg210_set_cxdone(fotg210);
		break;
	case USB_RECIP_ENDPOINT: {
		u8 epnum;
		epnum = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		if (epnum)
			fotg210_set_epnstall(fotg210->ep[epnum]);
		else
			fotg210_set_cxstall(fotg210);
		fotg210_set_cxdone(fotg210);
		}
		break;
	default:
		fotg210_request_error(fotg210);
		break;
	}
}