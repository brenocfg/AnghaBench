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
struct usb_hub {TYPE_1__** ports; } ;
struct usb_device {int maxchild; scalar_t__ state; int /*<<< orphan*/  active_duration; } ;
struct TYPE_2__ {struct usb_device* child; } ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 scalar_t__ jiffies ; 
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

__attribute__((used)) static void recursively_mark_NOTATTACHED(struct usb_device *udev)
{
	struct usb_hub *hub = usb_hub_to_struct_hub(udev);
	int i;

	for (i = 0; i < udev->maxchild; ++i) {
		if (hub->ports[i]->child)
			recursively_mark_NOTATTACHED(hub->ports[i]->child);
	}
	if (udev->state == USB_STATE_SUSPENDED)
		udev->active_duration -= jiffies;
	udev->state = USB_STATE_NOTATTACHED;
}