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
struct usbip_host_driver {int /*<<< orphan*/  edev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  udev_context ; 
 int /*<<< orphan*/  udev_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_exported_device_destroy (int /*<<< orphan*/ *) ; 

void usbip_generic_driver_close(struct usbip_host_driver *hdriver)
{
	if (!hdriver)
		return;

	usbip_exported_device_destroy(&hdriver->edev_list);

	udev_unref(udev_context);
}