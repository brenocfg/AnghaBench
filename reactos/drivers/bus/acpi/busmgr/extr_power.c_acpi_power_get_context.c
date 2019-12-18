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
struct acpi_power_resource {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_WARN ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 scalar_t__ acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

__attribute__((used)) static int
acpi_power_get_context (
	ACPI_HANDLE		handle,
	struct acpi_power_resource **resource)
{
	int			result = 0;
	struct acpi_device	*device = NULL;

	if (!resource)
		return_VALUE(-15);

	result = acpi_bus_get_device(handle, &device);
	if (result) {
		ACPI_DEBUG_PRINT((ACPI_DB_WARN, "Error getting context [%p]\n",
			handle));
		return_VALUE(result);
	}

	*resource = (struct acpi_power_resource *) acpi_driver_data(device);
	if (!*resource)
		return_VALUE(-15);

	return 0;
}