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
struct usb_ss_ep_comp_descriptor {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct usb_ep {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ USB_ENDPOINT_XFER_BULK ; 
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 struct usb_ep* gadget_find_ep_by_name (struct usb_gadget*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_type (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_gadget_ep_match_desc (struct usb_gadget*,struct usb_ep*,struct usb_endpoint_descriptor*,struct usb_ss_ep_comp_descriptor*) ; 

__attribute__((used)) static struct usb_ep *net2280_match_ep(struct usb_gadget *_gadget,
		struct usb_endpoint_descriptor *desc,
		struct usb_ss_ep_comp_descriptor *ep_comp)
{
	char name[8];
	struct usb_ep *ep;

	if (usb_endpoint_type(desc) == USB_ENDPOINT_XFER_INT) {
		/* ep-e, ep-f are PIO with only 64 byte fifos */
		ep = gadget_find_ep_by_name(_gadget, "ep-e");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
		ep = gadget_find_ep_by_name(_gadget, "ep-f");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
	}

	/* USB3380: Only first four endpoints have DMA channels. Allocate
	 * slower interrupt endpoints from PIO hw endpoints, to allow bulk/isoc
	 * endpoints use DMA hw endpoints.
	 */
	if (usb_endpoint_type(desc) == USB_ENDPOINT_XFER_INT &&
	    usb_endpoint_dir_in(desc)) {
		ep = gadget_find_ep_by_name(_gadget, "ep2in");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
		ep = gadget_find_ep_by_name(_gadget, "ep4in");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
	} else if (usb_endpoint_type(desc) == USB_ENDPOINT_XFER_INT &&
		   !usb_endpoint_dir_in(desc)) {
		ep = gadget_find_ep_by_name(_gadget, "ep1out");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
		ep = gadget_find_ep_by_name(_gadget, "ep3out");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
	} else if (usb_endpoint_type(desc) != USB_ENDPOINT_XFER_BULK &&
		   usb_endpoint_dir_in(desc)) {
		ep = gadget_find_ep_by_name(_gadget, "ep1in");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
		ep = gadget_find_ep_by_name(_gadget, "ep3in");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
	} else if (usb_endpoint_type(desc) != USB_ENDPOINT_XFER_BULK &&
		   !usb_endpoint_dir_in(desc)) {
		ep = gadget_find_ep_by_name(_gadget, "ep2out");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
		ep = gadget_find_ep_by_name(_gadget, "ep4out");
		if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			return ep;
	}

	/* USB3380: use same address for usb and hardware endpoints */
	snprintf(name, sizeof(name), "ep%d%s", usb_endpoint_num(desc),
			usb_endpoint_dir_in(desc) ? "in" : "out");
	ep = gadget_find_ep_by_name(_gadget, name);
	if (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
		return ep;

	return NULL;
}