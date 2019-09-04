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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct usb_ss_ep_comp_descriptor {int bmAttributes; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type_bulk; int /*<<< orphan*/  type_int; int /*<<< orphan*/  type_iso; int /*<<< orphan*/  dir_out; int /*<<< orphan*/  dir_in; } ;
struct usb_ep {scalar_t__ maxpacket_limit; int max_streams; TYPE_1__ caps; scalar_t__ claimed; } ;
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  gadget_is_dualspeed (struct usb_gadget*) ; 
 int /*<<< orphan*/  gadget_is_superspeed (struct usb_gadget*) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_maxp_mult (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_type (struct usb_endpoint_descriptor*) ; 

int usb_gadget_ep_match_desc(struct usb_gadget *gadget,
		struct usb_ep *ep, struct usb_endpoint_descriptor *desc,
		struct usb_ss_ep_comp_descriptor *ep_comp)
{
	u8		type;
	u16		max;
	int		num_req_streams = 0;

	/* endpoint already claimed? */
	if (ep->claimed)
		return 0;

	type = usb_endpoint_type(desc);
	max = usb_endpoint_maxp(desc);

	if (usb_endpoint_dir_in(desc) && !ep->caps.dir_in)
		return 0;
	if (usb_endpoint_dir_out(desc) && !ep->caps.dir_out)
		return 0;

	if (max > ep->maxpacket_limit)
		return 0;

	/* "high bandwidth" works only at high speed */
	if (!gadget_is_dualspeed(gadget) && usb_endpoint_maxp_mult(desc) > 1)
		return 0;

	switch (type) {
	case USB_ENDPOINT_XFER_CONTROL:
		/* only support ep0 for portable CONTROL traffic */
		return 0;
	case USB_ENDPOINT_XFER_ISOC:
		if (!ep->caps.type_iso)
			return 0;
		/* ISO:  limit 1023 bytes full speed, 1024 high/super speed */
		if (!gadget_is_dualspeed(gadget) && max > 1023)
			return 0;
		break;
	case USB_ENDPOINT_XFER_BULK:
		if (!ep->caps.type_bulk)
			return 0;
		if (ep_comp && gadget_is_superspeed(gadget)) {
			/* Get the number of required streams from the
			 * EP companion descriptor and see if the EP
			 * matches it
			 */
			num_req_streams = ep_comp->bmAttributes & 0x1f;
			if (num_req_streams > ep->max_streams)
				return 0;
		}
		break;
	case USB_ENDPOINT_XFER_INT:
		/* Bulk endpoints handle interrupt transfers,
		 * except the toggle-quirky iso-synch kind
		 */
		if (!ep->caps.type_int && !ep->caps.type_bulk)
			return 0;
		/* INT:  limit 64 bytes full speed, 1024 high/super speed */
		if (!gadget_is_dualspeed(gadget) && max > 64)
			return 0;
		break;
	}

	return 1;
}