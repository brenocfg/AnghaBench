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
struct usb_interface_descriptor {unsigned int bAlternateSetting; scalar_t__ bInterfaceClass; int bInterfaceSubClass; int bInterfaceProtocol; int bNumEndpoints; } ;
struct usb_interface {unsigned int num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_endpoint_descriptor {int bmAttributes; unsigned int bEndpointAddress; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_ENDPOINT_USAGE_IMPLICIT_FB ; 
 int USB_ENDPOINT_USAGE_MASK ; 
 struct usb_endpoint_descriptor* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int /*<<< orphan*/  usb_endpoint_is_isoc_in (struct usb_endpoint_descriptor*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 

__attribute__((used)) static int search_roland_implicit_fb(struct usb_device *dev, int ifnum,
				     unsigned int altsetting,
				     struct usb_host_interface **alts,
				     unsigned int *ep)
{
	struct usb_interface *iface;
	struct usb_interface_descriptor *altsd;
	struct usb_endpoint_descriptor *epd;

	iface = usb_ifnum_to_if(dev, ifnum);
	if (!iface || iface->num_altsetting < altsetting + 1)
		return -ENOENT;
	*alts = &iface->altsetting[altsetting];
	altsd = get_iface_desc(*alts);
	if (altsd->bAlternateSetting != altsetting ||
	    altsd->bInterfaceClass != USB_CLASS_VENDOR_SPEC ||
	    (altsd->bInterfaceSubClass != 2 &&
	     altsd->bInterfaceProtocol != 2   ) ||
	    altsd->bNumEndpoints < 1)
		return -ENOENT;
	epd = get_endpoint(*alts, 0);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_USAGE_MASK) !=
					USB_ENDPOINT_USAGE_IMPLICIT_FB)
		return -ENOENT;
	*ep = epd->bEndpointAddress;
	return 0;
}