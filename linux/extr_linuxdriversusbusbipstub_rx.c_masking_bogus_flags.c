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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {scalar_t__ state; struct usb_host_endpoint** ep_out; struct usb_host_endpoint** ep_in; } ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; } ;
struct urb {unsigned int transfer_flags; scalar_t__ setup_packet; int /*<<< orphan*/  pipe; struct usb_device* dev; int /*<<< orphan*/  complete; scalar_t__ hcpriv; } ;

/* Variables and functions */
 unsigned int URB_DIR_MASK ; 
 unsigned int URB_FREE_BUFFER ; 
 unsigned int URB_ISO_ASAP ; 
 unsigned int URB_NO_INTERRUPT ; 
 unsigned int URB_NO_TRANSFER_DMA_MAP ; 
 unsigned int URB_SHORT_NOT_OK ; 
 unsigned int URB_ZERO_PACKET ; 
 int USB_DIR_IN ; 
#define  USB_ENDPOINT_XFER_BULK 129 
 int USB_ENDPOINT_XFER_CONTROL ; 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ USB_STATE_UNAUTHENTICATED ; 
 int usb_endpoint_dir_out (int /*<<< orphan*/ *) ; 
 int usb_endpoint_type (int /*<<< orphan*/ *) ; 
 size_t usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void masking_bogus_flags(struct urb *urb)
{
	int				xfertype;
	struct usb_device		*dev;
	struct usb_host_endpoint	*ep;
	int				is_out;
	unsigned int	allowed;

	if (!urb || urb->hcpriv || !urb->complete)
		return;
	dev = urb->dev;
	if ((!dev) || (dev->state < USB_STATE_UNAUTHENTICATED))
		return;

	ep = (usb_pipein(urb->pipe) ? dev->ep_in : dev->ep_out)
		[usb_pipeendpoint(urb->pipe)];
	if (!ep)
		return;

	xfertype = usb_endpoint_type(&ep->desc);
	if (xfertype == USB_ENDPOINT_XFER_CONTROL) {
		struct usb_ctrlrequest *setup =
			(struct usb_ctrlrequest *) urb->setup_packet;

		if (!setup)
			return;
		is_out = !(setup->bRequestType & USB_DIR_IN) ||
			!setup->wLength;
	} else {
		is_out = usb_endpoint_dir_out(&ep->desc);
	}

	/* enforce simple/standard policy */
	allowed = (URB_NO_TRANSFER_DMA_MAP | URB_NO_INTERRUPT |
		   URB_DIR_MASK | URB_FREE_BUFFER);
	switch (xfertype) {
	case USB_ENDPOINT_XFER_BULK:
		if (is_out)
			allowed |= URB_ZERO_PACKET;
		/* FALLTHROUGH */
	default:			/* all non-iso endpoints */
		if (!is_out)
			allowed |= URB_SHORT_NOT_OK;
		break;
	case USB_ENDPOINT_XFER_ISOC:
		allowed |= URB_ISO_ASAP;
		break;
	}
	urb->transfer_flags &= allowed;
}