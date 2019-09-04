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
struct usb_bus {int busnum; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_MAXBUS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct usb_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bus_idr ; 
 int /*<<< orphan*/  usb_bus_idr_lock ; 
 int /*<<< orphan*/  usb_notify_add_bus (struct usb_bus*) ; 
 int /*<<< orphan*/  usbcore_name ; 

__attribute__((used)) static int usb_register_bus(struct usb_bus *bus)
{
	int result = -E2BIG;
	int busnum;

	mutex_lock(&usb_bus_idr_lock);
	busnum = idr_alloc(&usb_bus_idr, bus, 1, USB_MAXBUS, GFP_KERNEL);
	if (busnum < 0) {
		pr_err("%s: failed to get bus number\n", usbcore_name);
		goto error_find_busnum;
	}
	bus->busnum = busnum;
	mutex_unlock(&usb_bus_idr_lock);

	usb_notify_add_bus(bus);

	dev_info (bus->controller, "new USB bus registered, assigned bus "
		  "number %d\n", bus->busnum);
	return 0;

error_find_busnum:
	mutex_unlock(&usb_bus_idr_lock);
	return result;
}