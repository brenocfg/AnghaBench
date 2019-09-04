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
 scalar_t__ device_may_wakeup (struct device*) ; 
 int usb_phy_roothub_exit (struct usb_phy_roothub*) ; 
 int /*<<< orphan*/  usb_phy_roothub_power_off (struct usb_phy_roothub*) ; 

int usb_phy_roothub_suspend(struct device *controller_dev,
			    struct usb_phy_roothub *phy_roothub)
{
	usb_phy_roothub_power_off(phy_roothub);

	/* keep the PHYs initialized so the device can wake up the system */
	if (device_may_wakeup(controller_dev))
		return 0;

	return usb_phy_roothub_exit(phy_roothub);
}