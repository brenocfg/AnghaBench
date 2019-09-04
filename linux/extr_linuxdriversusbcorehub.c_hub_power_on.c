#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hub {TYPE_1__* hdev; int /*<<< orphan*/  power_bits; int /*<<< orphan*/  intfdev; } ;
struct TYPE_3__ {int maxchild; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hub_is_port_power_switchable (struct usb_hub*) ; 
 int /*<<< orphan*/  hub_power_on_good_delay (struct usb_hub*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_port_feature (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clear_port_feature (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hub_power_on(struct usb_hub *hub, bool do_delay)
{
	int port1;

	/* Enable power on each port.  Some hubs have reserved values
	 * of LPSM (> 2) in their descriptors, even though they are
	 * USB 2.0 hubs.  Some hubs do not implement port-power switching
	 * but only emulate it.  In all cases, the ports won't work
	 * unless we send these messages to the hub.
	 */
	if (hub_is_port_power_switchable(hub))
		dev_dbg(hub->intfdev, "enabling power on all ports\n");
	else
		dev_dbg(hub->intfdev, "trying to enable port power on "
				"non-switchable hub\n");
	for (port1 = 1; port1 <= hub->hdev->maxchild; port1++)
		if (test_bit(port1, hub->power_bits))
			set_port_feature(hub->hdev, port1, USB_PORT_FEAT_POWER);
		else
			usb_clear_port_feature(hub->hdev, port1,
						USB_PORT_FEAT_POWER);
	if (do_delay)
		msleep(hub_power_on_good_delay(hub));
}