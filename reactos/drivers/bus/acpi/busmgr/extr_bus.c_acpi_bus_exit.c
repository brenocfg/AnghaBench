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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_REMOVAL_NORMAL ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiRemoveNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTerminate () ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  acpi_bus_notify ; 
 int /*<<< orphan*/  acpi_bus_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_exit () ; 
 int /*<<< orphan*/  acpi_pci_link_exit () ; 
 int /*<<< orphan*/  acpi_pci_root_exit () ; 
 int /*<<< orphan*/  acpi_root ; 
 int /*<<< orphan*/  acpi_system_exit () ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
acpi_bus_exit (void)
{
	ACPI_STATUS		status = AE_OK;

	DPRINT1("acpi_bus_exit\n");

	status = AcpiRemoveNotifyHandler(ACPI_ROOT_OBJECT,
		ACPI_SYSTEM_NOTIFY, acpi_bus_notify);
	if (ACPI_FAILURE(status))
		DPRINT1("Error removing notify handler\n");

#ifdef CONFIG_ACPI_PCI
	acpi_pci_root_exit();
	acpi_pci_link_exit();
#endif
#ifdef CONFIG_ACPI_EC
	acpi_ec_exit();
#endif
	//acpi_power_exit();
	acpi_system_exit();

	acpi_bus_remove(acpi_root, ACPI_BUS_REMOVAL_NORMAL);

	status = AcpiTerminate();
	if (ACPI_FAILURE(status))
		DPRINT1("Unable to terminate the ACPI Interpreter\n");
	else
		DPRINT1("Interpreter disabled\n");

	return_VOID;
}