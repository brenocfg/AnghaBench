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
typedef  int uint32_t ;
struct TYPE_4__ {int nports; TYPE_1__* idev; } ;
struct TYPE_3__ {scalar_t__ status; int port; int /*<<< orphan*/  hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_SPEED_HIGH ; 
 int /*<<< orphan*/  HUB_SPEED_SUPER ; 
#define  USB_SPEED_SUPER 128 
 scalar_t__ VDEV_ST_NULL ; 
 TYPE_2__* vhci_driver ; 

int usbip_vhci_get_free_port(uint32_t speed)
{
	for (int i = 0; i < vhci_driver->nports; i++) {

		switch (speed) {
		case	USB_SPEED_SUPER:
			if (vhci_driver->idev[i].hub != HUB_SPEED_SUPER)
				continue;
		break;
		default:
			if (vhci_driver->idev[i].hub != HUB_SPEED_HIGH)
				continue;
		break;
		}

		if (vhci_driver->idev[i].status == VDEV_ST_NULL)
			return vhci_driver->idev[i].port;
	}

	return -1;
}