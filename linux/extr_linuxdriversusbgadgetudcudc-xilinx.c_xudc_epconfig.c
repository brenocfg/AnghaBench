#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xusb_udc {int /*<<< orphan*/  addr; int /*<<< orphan*/  (* write_fn ) (int /*<<< orphan*/ ,scalar_t__,int) ;} ;
struct TYPE_2__ {int maxpacket; } ;
struct xusb_ep {int is_in; int is_iso; int rambase; int buffer0count; int buffer1count; int epnumber; scalar_t__ buffer1ready; scalar_t__ buffer0ready; scalar_t__ offset; TYPE_1__ ep_usb; } ;

/* Variables and functions */
 scalar_t__ XUSB_BUFFREADY_OFFSET ; 
 scalar_t__ XUSB_EP_BUF0COUNT_OFFSET ; 
 scalar_t__ XUSB_EP_BUF1COUNT_OFFSET ; 
 int XUSB_STATUS_EP_BUFF2_SHIFT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void xudc_epconfig(struct xusb_ep *ep, struct xusb_udc *udc)
{
	u32 epcfgreg;

	/*
	 * Configure the end point direction, type, Max Packet Size and the
	 * EP buffer location.
	 */
	epcfgreg = ((ep->is_in << 29) | (ep->is_iso << 28) |
		   (ep->ep_usb.maxpacket << 15) | (ep->rambase));
	udc->write_fn(udc->addr, ep->offset, epcfgreg);

	/* Set the Buffer count and the Buffer ready bits.*/
	udc->write_fn(udc->addr, ep->offset + XUSB_EP_BUF0COUNT_OFFSET,
		      ep->buffer0count);
	udc->write_fn(udc->addr, ep->offset + XUSB_EP_BUF1COUNT_OFFSET,
		      ep->buffer1count);
	if (ep->buffer0ready)
		udc->write_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << ep->epnumber);
	if (ep->buffer1ready)
		udc->write_fn(udc->addr, XUSB_BUFFREADY_OFFSET,
			      1 << (ep->epnumber + XUSB_STATUS_EP_BUFF2_SHIFT));
}