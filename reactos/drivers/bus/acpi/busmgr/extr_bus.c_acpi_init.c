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
 int /*<<< orphan*/  ACPI_CA_VERSION ; 
 int /*<<< orphan*/  AcpiEventQueue ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExInitializeFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  acpi_bus_drivers_lock ; 
 int /*<<< orphan*/  acpi_bus_event_lock ; 
 int acpi_bus_init () ; 
 int /*<<< orphan*/  acpi_button_init () ; 
 int /*<<< orphan*/  acpi_pci_disabled ; 
 int /*<<< orphan*/  acpi_pci_link_init () ; 
 int /*<<< orphan*/  acpi_pci_root_init () ; 
 int /*<<< orphan*/  acpi_power_init () ; 
 int /*<<< orphan*/  acpi_system_init () ; 

int
acpi_init (void)
{
	int			result = 0;

	DPRINT("acpi_init\n");

	DPRINT("Subsystem revision %08x\n",ACPI_CA_VERSION);

	KeInitializeSpinLock(&acpi_bus_event_lock);
	KeInitializeEvent(&AcpiEventQueue, NotificationEvent, FALSE);
	ExInitializeFastMutex(&acpi_bus_drivers_lock);

	result = acpi_bus_init();

	//if (!result) {
		//pci_mmcfg_late_init();
		//if (!(pm_flags & PM_APM))
		//	pm_flags |= PM_ACPI;
		//else {
			//DPRINT1("APM is already active, exiting\n");
			//disable_acpi();
			//result = -ENODEV;
		//}
	//} else
	//	disable_acpi();

	/*
	 * If the laptop falls into the DMI check table, the power state check
	 * will be disabled in the course of device power transistion.
	 */
	//dmi_check_system(power_nocheck_dmi_table);

	/*
	 * Install drivers required for proper enumeration of the
	 * ACPI namespace.
	 */
	acpi_system_init();	/* ACPI System */
	acpi_power_init();	/* ACPI Bus Power Management */
	acpi_button_init();
	//acpi_ec_init();		/* ACPI Embedded Controller */
#ifdef CONFIG_ACPI_PCI
	if (!acpi_pci_disabled) {
		acpi_pci_link_init();	/* ACPI PCI Interrupt Link */
		acpi_pci_root_init();	/* ACPI PCI Root Bridge */
	}
#endif

	//acpi_scan_init();
	//acpi_ec_init();
	//acpi_power_init();
	//acpi_system_init();
	//acpi_debug_init();
	//acpi_sleep_proc_init();
	//acpi_wakeup_device_init();

	return result;
}