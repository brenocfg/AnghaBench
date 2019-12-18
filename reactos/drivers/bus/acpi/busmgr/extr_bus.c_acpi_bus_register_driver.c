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
struct acpi_driver {int /*<<< orphan*/  references; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  WALK_DOWN ; 
 int /*<<< orphan*/  acpi_bus_attach ; 
 int /*<<< orphan*/  acpi_bus_drivers ; 
 int /*<<< orphan*/  acpi_bus_drivers_lock ; 
 int /*<<< orphan*/  acpi_bus_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_driver*) ; 
 int /*<<< orphan*/  acpi_root ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int
acpi_bus_register_driver (
	struct acpi_driver	*driver)
{
	if (!driver)
		return_VALUE(AE_BAD_PARAMETER);

	//if (acpi_disabled)
	//	return_VALUE(AE_NOT_FOUND);

	down(&acpi_bus_drivers_lock);
	list_add_tail(&driver->node, &acpi_bus_drivers);
	up(&acpi_bus_drivers_lock);

	acpi_bus_walk(acpi_root, acpi_bus_attach,
		WALK_DOWN, driver);

	return_VALUE(driver->references);
}