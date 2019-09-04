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
struct usb_hub {int dummy; } ;
struct usb_device {int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int hub_port_disable (struct usb_hub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_hub_to_struct_hub (int /*<<< orphan*/ ) ; 

int usb_port_disable(struct usb_device *udev)
{
	struct usb_hub *hub = usb_hub_to_struct_hub(udev->parent);

	return hub_port_disable(hub, udev->portnum, 0);
}