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
struct TYPE_3__ {int /*<<< orphan*/  hc_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  udev_context ; 
 int /*<<< orphan*/  udev_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_unref (int /*<<< orphan*/ ) ; 
 TYPE_1__* vhci_driver ; 

void usbip_vhci_driver_close(void)
{
	if (!vhci_driver)
		return;

	udev_device_unref(vhci_driver->hc_device);

	free(vhci_driver);

	vhci_driver = NULL;

	udev_unref(udev_context);
}