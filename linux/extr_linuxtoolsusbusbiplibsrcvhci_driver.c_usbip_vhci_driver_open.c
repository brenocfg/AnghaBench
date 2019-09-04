#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbip_vhci_driver {int dummy; } ;
struct usbip_imported_device {int dummy; } ;
struct udev_device {int dummy; } ;
struct TYPE_4__ {int nports; int ncontrollers; struct udev_device* hc_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_VHCI_BUS_TYPE ; 
 int /*<<< orphan*/  USBIP_VHCI_DEVICE_NAME ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int get_ncontrollers () ; 
 int get_nports (struct udev_device*) ; 
 scalar_t__ refresh_imported_device_list () ; 
 int /*<<< orphan*/  udev_context ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 int /*<<< orphan*/  udev_new () ; 
 int /*<<< orphan*/  udev_unref (int /*<<< orphan*/ ) ; 
 TYPE_1__* vhci_driver ; 

int usbip_vhci_driver_open(void)
{
	int nports;
	struct udev_device *hc_device;

	udev_context = udev_new();
	if (!udev_context) {
		err("udev_new failed");
		return -1;
	}

	/* will be freed in usbip_driver_close() */
	hc_device =
		udev_device_new_from_subsystem_sysname(udev_context,
						       USBIP_VHCI_BUS_TYPE,
						       USBIP_VHCI_DEVICE_NAME);
	if (!hc_device) {
		err("udev_device_new_from_subsystem_sysname failed");
		goto err;
	}

	nports = get_nports(hc_device);
	if (nports <= 0) {
		err("no available ports");
		goto err;
	}
	dbg("available ports: %d", nports);

	vhci_driver = calloc(1, sizeof(struct usbip_vhci_driver) +
			nports * sizeof(struct usbip_imported_device));
	if (!vhci_driver) {
		err("vhci_driver allocation failed");
		goto err;
	}

	vhci_driver->nports = nports;
	vhci_driver->hc_device = hc_device;
	vhci_driver->ncontrollers = get_ncontrollers();
	dbg("available controllers: %d", vhci_driver->ncontrollers);

	if (vhci_driver->ncontrollers <=0) {
		err("no available usb controllers");
		goto err;
	}

	if (refresh_imported_device_list())
		goto err;

	return 0;

err:
	udev_device_unref(hc_device);

	if (vhci_driver)
		free(vhci_driver);

	vhci_driver = NULL;

	udev_unref(udev_context);

	return -1;
}