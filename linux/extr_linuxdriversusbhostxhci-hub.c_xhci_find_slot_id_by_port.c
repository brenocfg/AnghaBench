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
typedef  scalar_t__ u16 ;
struct xhci_hcd {TYPE_2__** devs; } ;
struct usb_hcd {scalar_t__ speed; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_4__ {scalar_t__ fake_port; TYPE_1__* udev; } ;
struct TYPE_3__ {int speed; } ;

/* Variables and functions */
 scalar_t__ HCD_USB3 ; 
 int MAX_HC_SLOTS ; 
 int USB_SPEED_SUPER ; 

int xhci_find_slot_id_by_port(struct usb_hcd *hcd, struct xhci_hcd *xhci,
		u16 port)
{
	int slot_id;
	int i;
	enum usb_device_speed speed;

	slot_id = 0;
	for (i = 0; i < MAX_HC_SLOTS; i++) {
		if (!xhci->devs[i] || !xhci->devs[i]->udev)
			continue;
		speed = xhci->devs[i]->udev->speed;
		if (((speed >= USB_SPEED_SUPER) == (hcd->speed >= HCD_USB3))
				&& xhci->devs[i]->fake_port == port) {
			slot_id = i;
			break;
		}
	}

	return slot_id;
}