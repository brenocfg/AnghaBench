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
struct usb_ssp_isoc_ep_comp_descriptor {scalar_t__ bDescriptorType; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {int /*<<< orphan*/  ssp_isoc_ep_comp; TYPE_1__ desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_DT_SSP_ISOC_ENDPOINT_COMP ; 
 int USB_DT_SSP_ISOC_EP_COMP_SIZE ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct usb_ssp_isoc_ep_comp_descriptor*,int) ; 

__attribute__((used)) static void usb_parse_ssp_isoc_endpoint_companion(struct device *ddev,
		int cfgno, int inum, int asnum, struct usb_host_endpoint *ep,
		unsigned char *buffer, int size)
{
	struct usb_ssp_isoc_ep_comp_descriptor *desc;

	/*
	 * The SuperSpeedPlus Isoc endpoint companion descriptor immediately
	 * follows the SuperSpeed Endpoint Companion descriptor
	 */
	desc = (struct usb_ssp_isoc_ep_comp_descriptor *) buffer;
	if (desc->bDescriptorType != USB_DT_SSP_ISOC_ENDPOINT_COMP ||
	    size < USB_DT_SSP_ISOC_EP_COMP_SIZE) {
		dev_warn(ddev, "Invalid SuperSpeedPlus isoc endpoint companion"
			 "for config %d interface %d altsetting %d ep %d.\n",
			 cfgno, inum, asnum, ep->desc.bEndpointAddress);
		return;
	}
	memcpy(&ep->ssp_isoc_ep_comp, desc, USB_DT_SSP_ISOC_EP_COMP_SIZE);
}