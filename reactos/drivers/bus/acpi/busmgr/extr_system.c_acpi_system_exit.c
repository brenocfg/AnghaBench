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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_system_driver ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_system_exit (void)
{
	ACPI_FUNCTION_TRACE("acpi_system_exit");
	acpi_bus_unregister_driver(&acpi_system_driver);
	return_VOID;
}