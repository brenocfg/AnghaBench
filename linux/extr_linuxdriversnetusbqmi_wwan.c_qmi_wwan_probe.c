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
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceNumber; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_1__* cur_altsetting; } ;
struct usb_device_id {unsigned long driver_info; int match_flags; } ;
struct TYPE_2__ {struct usb_interface_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_DEVICE_ID_MATCH_INT_NUMBER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  qmi_wwan_info ; 
 scalar_t__ quectel_diag_detected (struct usb_interface*) ; 
 scalar_t__ quectel_ec20_detected (struct usb_interface*) ; 
 int usbnet_probe (struct usb_interface*,struct usb_device_id*) ; 

__attribute__((used)) static int qmi_wwan_probe(struct usb_interface *intf,
			  const struct usb_device_id *prod)
{
	struct usb_device_id *id = (struct usb_device_id *)prod;
	struct usb_interface_descriptor *desc = &intf->cur_altsetting->desc;

	/* Workaround to enable dynamic IDs.  This disables usbnet
	 * blacklisting functionality.  Which, if required, can be
	 * reimplemented here by using a magic "blacklist" value
	 * instead of 0 in the static device id table
	 */
	if (!id->driver_info) {
		dev_dbg(&intf->dev, "setting defaults for dynamic device id\n");
		id->driver_info = (unsigned long)&qmi_wwan_info;
	}

	/* There are devices where the same interface number can be
	 * configured as different functions. We should only bind to
	 * vendor specific functions when matching on interface number
	 */
	if (id->match_flags & USB_DEVICE_ID_MATCH_INT_NUMBER &&
	    desc->bInterfaceClass != USB_CLASS_VENDOR_SPEC) {
		dev_dbg(&intf->dev,
			"Rejecting interface number match for class %02x\n",
			desc->bInterfaceClass);
		return -ENODEV;
	}

	/* Quectel EC20 quirk where we've QMI on interface 4 instead of 0 */
	if (quectel_ec20_detected(intf) && desc->bInterfaceNumber == 0) {
		dev_dbg(&intf->dev, "Quectel EC20 quirk, skipping interface 0\n");
		return -ENODEV;
	}

	/* Several Quectel modems supports dynamic interface configuration, so
	 * we need to match on class/subclass/protocol. These values are
	 * identical for the diagnostic- and QMI-interface, but bNumEndpoints is
	 * different. Ignore the current interface if the number of endpoints
	 * the number for the diag interface (two).
	 */
	if (quectel_diag_detected(intf))
		return -ENODEV;

	return usbnet_probe(intf, id);
}