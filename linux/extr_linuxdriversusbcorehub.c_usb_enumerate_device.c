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
struct usb_hcd {scalar_t__ tpl_support; } ;
struct TYPE_3__ {int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  iProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_2__* bus; TYPE_1__ descriptor; void* serial; void* manufacturer; void* product; int /*<<< orphan*/ * config; } ;
struct TYPE_4__ {scalar_t__ is_b_host; scalar_t__ b_hnp_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_OTG ; 
 int /*<<< orphan*/  CONFIG_USB_OTG_WHITELIST ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMSG_AUTO_SUSPEND ; 
 struct usb_hcd* bus_to_hcd (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  is_targeted (struct usb_device*) ; 
 void* usb_cache_string (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_detect_interface_quirks (struct usb_device*) ; 
 int usb_enumerate_device_otg (struct usb_device*) ; 
 int usb_get_configuration (struct usb_device*) ; 
 int usb_port_suspend (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_enumerate_device(struct usb_device *udev)
{
	int err;
	struct usb_hcd *hcd = bus_to_hcd(udev->bus);

	if (udev->config == NULL) {
		err = usb_get_configuration(udev);
		if (err < 0) {
			if (err != -ENODEV)
				dev_err(&udev->dev, "can't read configurations, error %d\n",
						err);
			return err;
		}
	}

	/* read the standard strings and cache them if present */
	udev->product = usb_cache_string(udev, udev->descriptor.iProduct);
	udev->manufacturer = usb_cache_string(udev,
					      udev->descriptor.iManufacturer);
	udev->serial = usb_cache_string(udev, udev->descriptor.iSerialNumber);

	err = usb_enumerate_device_otg(udev);
	if (err < 0)
		return err;

	if (IS_ENABLED(CONFIG_USB_OTG_WHITELIST) && hcd->tpl_support &&
		!is_targeted(udev)) {
		/* Maybe it can talk to us, though we can't talk to it.
		 * (Includes HNP test device.)
		 */
		if (IS_ENABLED(CONFIG_USB_OTG) && (udev->bus->b_hnp_enable
			|| udev->bus->is_b_host)) {
			err = usb_port_suspend(udev, PMSG_AUTO_SUSPEND);
			if (err < 0)
				dev_dbg(&udev->dev, "HNP fail, %d\n", err);
		}
		return -ENOTSUPP;
	}

	usb_detect_interface_quirks(udev);

	return 0;
}