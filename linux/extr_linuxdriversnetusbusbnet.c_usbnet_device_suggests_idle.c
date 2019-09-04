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
struct usbnet {TYPE_1__* intf; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEVICE_REPORT_IDLE ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (TYPE_1__*) ; 

void usbnet_device_suggests_idle(struct usbnet *dev)
{
	if (!test_and_set_bit(EVENT_DEVICE_REPORT_IDLE, &dev->flags)) {
		dev->intf->needs_remote_wakeup = 1;
		usb_autopm_put_interface_async(dev->intf);
	}
}