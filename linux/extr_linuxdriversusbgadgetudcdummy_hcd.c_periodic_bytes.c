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
struct TYPE_3__ {int maxpacket; } ;
struct dummy_ep {int /*<<< orphan*/  desc; TYPE_1__ ep; } ;
struct TYPE_4__ {scalar_t__ speed; } ;
struct dummy {TYPE_2__ gadget; } ;

/* Variables and functions */
#define  USB_ENDPOINT_XFER_BULK 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int usb_endpoint_maxp_mult (int /*<<< orphan*/ ) ; 
 int usb_endpoint_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int periodic_bytes(struct dummy *dum, struct dummy_ep *ep)
{
	int	limit = ep->ep.maxpacket;

	if (dum->gadget.speed == USB_SPEED_HIGH) {
		int	tmp;

		/* high bandwidth mode */
		tmp = usb_endpoint_maxp_mult(ep->desc);
		tmp *= 8 /* applies to entire frame */;
		limit += limit * tmp;
	}
	if (dum->gadget.speed == USB_SPEED_SUPER) {
		switch (usb_endpoint_type(ep->desc)) {
		case USB_ENDPOINT_XFER_ISOC:
			/* Sec. 4.4.8.2 USB3.0 Spec */
			limit = 3 * 16 * 1024 * 8;
			break;
		case USB_ENDPOINT_XFER_INT:
			/* Sec. 4.4.7.2 USB3.0 Spec */
			limit = 3 * 1024 * 8;
			break;
		case USB_ENDPOINT_XFER_BULK:
		default:
			break;
		}
	}
	return limit;
}