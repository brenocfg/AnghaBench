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
struct acpi_driver {int /*<<< orphan*/  node; scalar_t__ references; } ;

/* Variables and functions */
 int /*<<< orphan*/  WALK_UP ; 
 int /*<<< orphan*/  acpi_bus_drivers_lock ; 
 int /*<<< orphan*/  acpi_bus_unattach ; 
 int /*<<< orphan*/  acpi_bus_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_driver*) ; 
 int /*<<< orphan*/  acpi_root ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void
acpi_bus_unregister_driver (
	struct acpi_driver	*driver)
{
	if (!driver)
		return;

	acpi_bus_walk(acpi_root, acpi_bus_unattach, WALK_UP, driver);

	if (driver->references)
		return;

	down(&acpi_bus_drivers_lock);
	list_del(&driver->node);
	up(&acpi_bus_drivers_lock);

	return;
}