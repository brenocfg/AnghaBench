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
struct usb_phy_roothub {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  usb_phy_roothub_exit (struct usb_phy_roothub*) ; 
 int usb_phy_roothub_init (struct usb_phy_roothub*) ; 
 int usb_phy_roothub_power_on (struct usb_phy_roothub*) ; 

int usb_phy_roothub_resume(struct device *controller_dev,
			   struct usb_phy_roothub *phy_roothub)
{
	int err;

	/* if the device can't wake up the system _exit was called */
	if (!device_may_wakeup(controller_dev)) {
		err = usb_phy_roothub_init(phy_roothub);
		if (err)
			return err;
	}

	err = usb_phy_roothub_power_on(phy_roothub);

	/* undo _init if _power_on failed */
	if (err && !device_may_wakeup(controller_dev))
		usb_phy_roothub_exit(phy_roothub);

	return err;
}