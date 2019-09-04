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
struct usbip_host_driver {int /*<<< orphan*/  edev_list; scalar_t__ ndevs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int refresh_exported_devices (struct usbip_host_driver*) ; 
 int /*<<< orphan*/  usbip_exported_device_destroy (int /*<<< orphan*/ *) ; 

int usbip_generic_refresh_device_list(struct usbip_host_driver *hdriver)
{
	int rc;

	usbip_exported_device_destroy(&hdriver->edev_list);

	hdriver->ndevs = 0;
	INIT_LIST_HEAD(&hdriver->edev_list);

	rc = refresh_exported_devices(hdriver);
	if (rc < 0)
		return -1;

	return 0;
}