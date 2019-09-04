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
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct renesas_usb3 {scalar_t__ phy; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_SPEED_FULL ; 
 struct renesas_usb3* gadget_to_renesas_usb3 (struct usb_gadget*) ; 
 int /*<<< orphan*/  phy_init (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renesas_usb3_init_controller (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_to_dev (struct renesas_usb3*) ; 

__attribute__((used)) static int renesas_usb3_start(struct usb_gadget *gadget,
			      struct usb_gadget_driver *driver)
{
	struct renesas_usb3 *usb3;

	if (!driver || driver->max_speed < USB_SPEED_FULL ||
	    !driver->setup)
		return -EINVAL;

	usb3 = gadget_to_renesas_usb3(gadget);

	/* hook up the driver */
	usb3->driver = driver;

	if (usb3->phy)
		phy_init(usb3->phy);

	pm_runtime_get_sync(usb3_to_dev(usb3));

	renesas_usb3_init_controller(usb3);

	return 0;
}