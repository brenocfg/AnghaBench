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
struct usb_port {int /*<<< orphan*/  dev; struct usb_device* child; } ;
struct usb_hub {int mA_per_port; int /*<<< orphan*/  intfdev; struct usb_port** ports; TYPE_1__* descriptor; int /*<<< orphan*/  limited_power; struct usb_device* hdev; } ;
struct usb_device {int bus_mA; int maxchild; scalar_t__ parent; TYPE_2__* bus; scalar_t__ actconfig; } ;
struct TYPE_4__ {int otg_port; } ;
struct TYPE_3__ {int bHubContrCurrent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int usb_get_max_power (struct usb_device*,scalar_t__) ; 

__attribute__((used)) static unsigned
hub_power_remaining(struct usb_hub *hub)
{
	struct usb_device *hdev = hub->hdev;
	int remaining;
	int port1;

	if (!hub->limited_power)
		return 0;

	remaining = hdev->bus_mA - hub->descriptor->bHubContrCurrent;
	for (port1 = 1; port1 <= hdev->maxchild; ++port1) {
		struct usb_port *port_dev = hub->ports[port1 - 1];
		struct usb_device *udev = port_dev->child;
		unsigned unit_load;
		int delta;

		if (!udev)
			continue;
		if (hub_is_superspeed(udev))
			unit_load = 150;
		else
			unit_load = 100;

		/*
		 * Unconfigured devices may not use more than one unit load,
		 * or 8mA for OTG ports
		 */
		if (udev->actconfig)
			delta = usb_get_max_power(udev, udev->actconfig);
		else if (port1 != udev->bus->otg_port || hdev->parent)
			delta = unit_load;
		else
			delta = 8;
		if (delta > hub->mA_per_port)
			dev_warn(&port_dev->dev, "%dmA is over %umA budget!\n",
					delta, hub->mA_per_port);
		remaining -= delta;
	}
	if (remaining < 0) {
		dev_warn(hub->intfdev, "%dmA over power budget!\n",
			-remaining);
		remaining = 0;
	}
	return remaining;
}