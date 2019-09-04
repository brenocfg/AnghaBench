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
struct usbip_host_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 int refresh_exported_devices (struct usbip_host_driver*) ; 
 int /*<<< orphan*/  udev_context ; 
 int /*<<< orphan*/  udev_new () ; 
 int /*<<< orphan*/  udev_unref (int /*<<< orphan*/ ) ; 

int usbip_generic_driver_open(struct usbip_host_driver *hdriver)
{
	int rc;

	udev_context = udev_new();
	if (!udev_context) {
		err("udev_new failed");
		return -1;
	}

	rc = refresh_exported_devices(hdriver);
	if (rc < 0)
		goto err;
	return 0;
err:
	udev_unref(udev_context);
	return -1;
}