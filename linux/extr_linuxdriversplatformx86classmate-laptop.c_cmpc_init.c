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
 int acpi_bus_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpc_accel_acpi_driver ; 
 int /*<<< orphan*/  cmpc_accel_acpi_driver_v4 ; 
 int /*<<< orphan*/  cmpc_ipml_acpi_driver ; 
 int /*<<< orphan*/  cmpc_keys_acpi_driver ; 
 int /*<<< orphan*/  cmpc_tablet_acpi_driver ; 

__attribute__((used)) static int cmpc_init(void)
{
	int r;

	r = acpi_bus_register_driver(&cmpc_keys_acpi_driver);
	if (r)
		goto failed_keys;

	r = acpi_bus_register_driver(&cmpc_ipml_acpi_driver);
	if (r)
		goto failed_bl;

	r = acpi_bus_register_driver(&cmpc_tablet_acpi_driver);
	if (r)
		goto failed_tablet;

	r = acpi_bus_register_driver(&cmpc_accel_acpi_driver);
	if (r)
		goto failed_accel;

	r = acpi_bus_register_driver(&cmpc_accel_acpi_driver_v4);
	if (r)
		goto failed_accel_v4;

	return r;

failed_accel_v4:
	acpi_bus_unregister_driver(&cmpc_accel_acpi_driver);

failed_accel:
	acpi_bus_unregister_driver(&cmpc_tablet_acpi_driver);

failed_tablet:
	acpi_bus_unregister_driver(&cmpc_ipml_acpi_driver);

failed_bl:
	acpi_bus_unregister_driver(&cmpc_keys_acpi_driver);

failed_keys:
	return r;
}