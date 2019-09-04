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
struct acpiphp_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_scan_lock_acquire () ; 
 int /*<<< orphan*/  acpi_scan_lock_release () ; 
 int acpiphp_disable_and_eject_slot (struct acpiphp_slot*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 

int acpiphp_disable_slot(struct acpiphp_slot *slot)
{
	int ret;

	/*
	 * Acquire acpi_scan_lock to ensure that the execution of _EJ0 in
	 * acpiphp_disable_and_eject_slot() will be synchronized properly.
	 */
	acpi_scan_lock_acquire();
	pci_lock_rescan_remove();
	ret = acpiphp_disable_and_eject_slot(slot);
	pci_unlock_rescan_remove();
	acpi_scan_lock_release();
	return ret;
}