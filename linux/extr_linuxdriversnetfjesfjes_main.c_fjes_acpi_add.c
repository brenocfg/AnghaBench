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
struct platform_device {int dummy; } ;
struct acpi_device {struct platform_device* driver_data; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 scalar_t__ acpi_check_extended_socket_status (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fjes_get_acpi_resource ; 
 int /*<<< orphan*/  fjes_resource ; 
 int /*<<< orphan*/  is_extended_socket_device (struct acpi_device*) ; 
 struct platform_device* platform_device_register_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fjes_acpi_add(struct acpi_device *device)
{
	struct platform_device *plat_dev;
	acpi_status status;

	if (!is_extended_socket_device(device))
		return -ENODEV;

	if (acpi_check_extended_socket_status(device))
		return -ENODEV;

	status = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
				     fjes_get_acpi_resource, fjes_resource);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	/* create platform_device */
	plat_dev = platform_device_register_simple(DRV_NAME, 0, fjes_resource,
						   ARRAY_SIZE(fjes_resource));
	device->driver_data = plat_dev;

	return 0;
}