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
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpc_accel_acpi_driver ; 
 int /*<<< orphan*/  cmpc_accel_acpi_driver_v4 ; 
 int /*<<< orphan*/  cmpc_ipml_acpi_driver ; 
 int /*<<< orphan*/  cmpc_keys_acpi_driver ; 
 int /*<<< orphan*/  cmpc_tablet_acpi_driver ; 

__attribute__((used)) static void cmpc_exit(void)
{
	acpi_bus_unregister_driver(&cmpc_accel_acpi_driver_v4);
	acpi_bus_unregister_driver(&cmpc_accel_acpi_driver);
	acpi_bus_unregister_driver(&cmpc_tablet_acpi_driver);
	acpi_bus_unregister_driver(&cmpc_ipml_acpi_driver);
	acpi_bus_unregister_driver(&cmpc_keys_acpi_driver);
}