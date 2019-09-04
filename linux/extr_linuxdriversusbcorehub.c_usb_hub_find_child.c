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
struct usb_device {int maxchild; } ;
struct TYPE_2__ {struct usb_device* child; } ;

/* Variables and functions */
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

struct usb_device *usb_hub_find_child(struct usb_device *hdev,
		int port1)
{
	struct usb_hub *hub = usb_hub_to_struct_hub(hdev);

	if (port1 < 1 || port1 > hdev->maxchild)
		return NULL;
	return hub->ports[port1 - 1]->child;
}