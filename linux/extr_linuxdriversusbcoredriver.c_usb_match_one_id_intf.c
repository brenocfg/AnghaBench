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
struct TYPE_4__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; scalar_t__ bInterfaceNumber; } ;
struct usb_host_interface {TYPE_2__ desc; } ;
struct usb_device_id {int match_flags; scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; scalar_t__ bInterfaceNumber; } ;
struct TYPE_3__ {scalar_t__ bDeviceClass; } ;
struct usb_device {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_DEVICE_ID_MATCH_INT_CLASS ; 
 int USB_DEVICE_ID_MATCH_INT_NUMBER ; 
 int USB_DEVICE_ID_MATCH_INT_PROTOCOL ; 
 int USB_DEVICE_ID_MATCH_INT_SUBCLASS ; 
 int USB_DEVICE_ID_MATCH_VENDOR ; 

int usb_match_one_id_intf(struct usb_device *dev,
			  struct usb_host_interface *intf,
			  const struct usb_device_id *id)
{
	/* The interface class, subclass, protocol and number should never be
	 * checked for a match if the device class is Vendor Specific,
	 * unless the match record specifies the Vendor ID. */
	if (dev->descriptor.bDeviceClass == USB_CLASS_VENDOR_SPEC &&
			!(id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
			(id->match_flags & (USB_DEVICE_ID_MATCH_INT_CLASS |
				USB_DEVICE_ID_MATCH_INT_SUBCLASS |
				USB_DEVICE_ID_MATCH_INT_PROTOCOL |
				USB_DEVICE_ID_MATCH_INT_NUMBER)))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_CLASS) &&
	    (id->bInterfaceClass != intf->desc.bInterfaceClass))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_SUBCLASS) &&
	    (id->bInterfaceSubClass != intf->desc.bInterfaceSubClass))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_PROTOCOL) &&
	    (id->bInterfaceProtocol != intf->desc.bInterfaceProtocol))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_INT_NUMBER) &&
	    (id->bInterfaceNumber != intf->desc.bInterfaceNumber))
		return 0;

	return 1;
}