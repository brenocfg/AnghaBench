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
struct usb_port {int portnum; int location; int /*<<< orphan*/  connect_type; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct usb_device {int /*<<< orphan*/  portnum; scalar_t__ parent; TYPE_1__ dev; int /*<<< orphan*/  bus; } ;
struct device {TYPE_1__* parent; } ;
struct acpi_pld_info {int group_token; int group_position; } ;
struct acpi_device {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (TYPE_1__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_pld_info*) ; 
 int USB_ACPI_LOCATION_VALID ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 struct acpi_device* acpi_find_child_device (struct acpi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_get_physical_device_location (int /*<<< orphan*/ *,struct acpi_pld_info**) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 scalar_t__ is_usb_device (struct device*) ; 
 scalar_t__ is_usb_port (struct device*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 struct usb_port* to_usb_port (struct device*) ; 
 struct acpi_device* usb_acpi_find_port (struct acpi_device*,int) ; 
 int /*<<< orphan*/  usb_acpi_get_connect_type (int /*<<< orphan*/ *,struct acpi_pld_info*) ; 
 int /*<<< orphan*/ * usb_get_hub_port_acpi_handle (scalar_t__,int /*<<< orphan*/ ) ; 
 int usb_hcd_find_raw_port_number (struct usb_hcd*,int) ; 

__attribute__((used)) static struct acpi_device *usb_acpi_find_companion(struct device *dev)
{
	struct usb_device *udev;
	struct acpi_device *adev;
	acpi_handle *parent_handle;

	/*
	 * In the ACPI DSDT table, only usb root hub and usb ports are
	 * acpi device nodes. The hierarchy like following.
	 * Device (EHC1)
	 *	Device (HUBN)
	 *		Device (PR01)
	 *			Device (PR11)
	 *			Device (PR12)
	 *			Device (PR13)
	 *			...
	 * So all binding process is divided into two parts. binding
	 * root hub and usb ports.
	 */
	if (is_usb_device(dev)) {
		udev = to_usb_device(dev);
		if (udev->parent)
			return NULL;

		/* root hub is only child (_ADR=0) under its parent, the HC */
		adev = ACPI_COMPANION(dev->parent);
		return acpi_find_child_device(adev, 0, false);
	} else if (is_usb_port(dev)) {
		struct usb_port *port_dev = to_usb_port(dev);
		int port1 = port_dev->portnum;
		struct acpi_pld_info *pld;
		acpi_handle *handle;
		acpi_status status;

		/* Get the struct usb_device point of port's hub */
		udev = to_usb_device(dev->parent->parent);

		/*
		 * The root hub ports' parent is the root hub. The non-root-hub
		 * ports' parent is the parent hub port which the hub is
		 * connected to.
		 */
		if (!udev->parent) {
			struct usb_hcd *hcd = bus_to_hcd(udev->bus);
			int raw;

			raw = usb_hcd_find_raw_port_number(hcd, port1);

			adev = usb_acpi_find_port(ACPI_COMPANION(&udev->dev),
						  raw);

			if (!adev)
				return NULL;
		} else {
			parent_handle =
				usb_get_hub_port_acpi_handle(udev->parent,
				udev->portnum);
			if (!parent_handle)
				return NULL;

			acpi_bus_get_device(parent_handle, &adev);

			adev = usb_acpi_find_port(adev, port1);

			if (!adev)
				return NULL;
		}
		handle = adev->handle;
		status = acpi_get_physical_device_location(handle, &pld);
		if (ACPI_FAILURE(status) || !pld)
			return adev;

		port_dev->location = USB_ACPI_LOCATION_VALID
			| pld->group_token << 8 | pld->group_position;
		port_dev->connect_type = usb_acpi_get_connect_type(handle, pld);
		ACPI_FREE(pld);

		return adev;
	}

	return NULL;
}