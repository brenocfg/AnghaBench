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
struct usbip_imported_device {int dummy; } ;
struct TYPE_2__ {int nports; struct usbip_imported_device* idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIDS_FILE ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  usbip_names_free () ; 
 scalar_t__ usbip_names_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_vhci_driver_close () ; 
 int usbip_vhci_driver_open () ; 
 scalar_t__ usbip_vhci_imported_device_dump (struct usbip_imported_device*) ; 
 TYPE_1__* vhci_driver ; 

__attribute__((used)) static int list_imported_devices(void)
{
	int i;
	struct usbip_imported_device *idev;
	int ret;

	if (usbip_names_init(USBIDS_FILE))
		err("failed to open %s", USBIDS_FILE);

	ret = usbip_vhci_driver_open();
	if (ret < 0) {
		err("open vhci_driver");
		goto err_names_free;
	}

	printf("Imported USB devices\n");
	printf("====================\n");

	for (i = 0; i < vhci_driver->nports; i++) {
		idev = &vhci_driver->idev[i];

		if (usbip_vhci_imported_device_dump(idev) < 0)
			goto err_driver_close;
	}

	usbip_vhci_driver_close();
	usbip_names_free();

	return ret;

err_driver_close:
	usbip_vhci_driver_close();
err_names_free:
	usbip_names_free();
	return -1;
}