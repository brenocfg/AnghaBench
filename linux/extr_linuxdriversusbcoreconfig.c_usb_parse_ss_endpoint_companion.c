#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_ss_ep_comp_descriptor {scalar_t__ bDescriptorType; int bMaxBurst; int bmAttributes; int /*<<< orphan*/  wBytesPerInterval; scalar_t__ bLength; } ;
struct TYPE_7__ {int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_8__ {int bLength; int bMaxBurst; int bmAttributes; int /*<<< orphan*/  wBytesPerInterval; scalar_t__ bDescriptorType; } ;
struct usb_host_endpoint {TYPE_1__ desc; TYPE_6__ ss_ep_comp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_DT_SS_ENDPOINT_COMP ; 
 int USB_DT_SS_EP_COMP_SIZE ; 
 int USB_SS_MULT (int) ; 
 scalar_t__ USB_SS_SSP_ISOC_COMP (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,struct usb_ss_ep_comp_descriptor*,int) ; 
 int usb_endpoint_maxp (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_xfer_bulk (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_xfer_control (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_xfer_int (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_xfer_isoc (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_parse_ssp_isoc_endpoint_companion (struct device*,int,int,int,struct usb_host_endpoint*,unsigned char*,int) ; 

__attribute__((used)) static void usb_parse_ss_endpoint_companion(struct device *ddev, int cfgno,
		int inum, int asnum, struct usb_host_endpoint *ep,
		unsigned char *buffer, int size)
{
	struct usb_ss_ep_comp_descriptor *desc;
	int max_tx;

	/* The SuperSpeed endpoint companion descriptor is supposed to
	 * be the first thing immediately following the endpoint descriptor.
	 */
	desc = (struct usb_ss_ep_comp_descriptor *) buffer;

	if (desc->bDescriptorType != USB_DT_SS_ENDPOINT_COMP ||
			size < USB_DT_SS_EP_COMP_SIZE) {
		dev_warn(ddev, "No SuperSpeed endpoint companion for config %d "
				" interface %d altsetting %d ep %d: "
				"using minimum values\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddress);

		/* Fill in some default values.
		 * Leave bmAttributes as zero, which will mean no streams for
		 * bulk, and isoc won't support multiple bursts of packets.
		 * With bursts of only one packet, and a Mult of 1, the max
		 * amount of data moved per endpoint service interval is one
		 * packet.
		 */
		ep->ss_ep_comp.bLength = USB_DT_SS_EP_COMP_SIZE;
		ep->ss_ep_comp.bDescriptorType = USB_DT_SS_ENDPOINT_COMP;
		if (usb_endpoint_xfer_isoc(&ep->desc) ||
				usb_endpoint_xfer_int(&ep->desc))
			ep->ss_ep_comp.wBytesPerInterval =
					ep->desc.wMaxPacketSize;
		return;
	}
	buffer += desc->bLength;
	size -= desc->bLength;
	memcpy(&ep->ss_ep_comp, desc, USB_DT_SS_EP_COMP_SIZE);

	/* Check the various values */
	if (usb_endpoint_xfer_control(&ep->desc) && desc->bMaxBurst != 0) {
		dev_warn(ddev, "Control endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		ep->ss_ep_comp.bMaxBurst = 0;
	} else if (desc->bMaxBurst > 15) {
		dev_warn(ddev, "Endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 15\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		ep->ss_ep_comp.bMaxBurst = 15;
	}

	if ((usb_endpoint_xfer_control(&ep->desc) ||
			usb_endpoint_xfer_int(&ep->desc)) &&
				desc->bmAttributes != 0) {
		dev_warn(ddev, "%s endpoint with bmAttributes = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n",
				usb_endpoint_xfer_control(&ep->desc) ? "Control" : "Bulk",
				desc->bmAttributes,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		ep->ss_ep_comp.bmAttributes = 0;
	} else if (usb_endpoint_xfer_bulk(&ep->desc) &&
			desc->bmAttributes > 16) {
		dev_warn(ddev, "Bulk endpoint with more than 65536 streams in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to max\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		ep->ss_ep_comp.bmAttributes = 16;
	} else if (usb_endpoint_xfer_isoc(&ep->desc) &&
		   !USB_SS_SSP_ISOC_COMP(desc->bmAttributes) &&
		   USB_SS_MULT(desc->bmAttributes) > 3) {
		dev_warn(ddev, "Isoc endpoint has Mult of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 3\n",
				USB_SS_MULT(desc->bmAttributes),
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		ep->ss_ep_comp.bmAttributes = 2;
	}

	if (usb_endpoint_xfer_isoc(&ep->desc))
		max_tx = (desc->bMaxBurst + 1) *
			(USB_SS_MULT(desc->bmAttributes)) *
			usb_endpoint_maxp(&ep->desc);
	else if (usb_endpoint_xfer_int(&ep->desc))
		max_tx = usb_endpoint_maxp(&ep->desc) *
			(desc->bMaxBurst + 1);
	else
		max_tx = 999999;
	if (le16_to_cpu(desc->wBytesPerInterval) > max_tx) {
		dev_warn(ddev, "%s endpoint with wBytesPerInterval of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to %d\n",
				usb_endpoint_xfer_isoc(&ep->desc) ? "Isoc" : "Int",
				le16_to_cpu(desc->wBytesPerInterval),
				cfgno, inum, asnum, ep->desc.bEndpointAddress,
				max_tx);
		ep->ss_ep_comp.wBytesPerInterval = cpu_to_le16(max_tx);
	}
	/* Parse a possible SuperSpeedPlus isoc ep companion descriptor */
	if (usb_endpoint_xfer_isoc(&ep->desc) &&
	    USB_SS_SSP_ISOC_COMP(desc->bmAttributes))
		usb_parse_ssp_isoc_endpoint_companion(ddev, cfgno, inum, asnum,
							ep, buffer, size);
}