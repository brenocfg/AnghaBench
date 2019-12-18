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
struct acpi_system {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (struct acpi_system*,char) ; 
 scalar_t__ acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

__attribute__((used)) static int
acpi_system_remove (
	struct acpi_device	*device,
	int			type)
{
	struct acpi_system	*system = NULL;

	ACPI_FUNCTION_TRACE("acpi_system_remove");

	if (!device || !acpi_driver_data(device))
		return_VALUE(-1);

	system = (struct acpi_system *) acpi_driver_data(device);

//#ifdef CONFIG_PM
//	/* Remove the soft-off (S5) handler. */
//	if (system->states[ACPI_STATE_S5]) {
//		unregister_sysrq_key('o', &sysrq_acpi_poweroff_op);
//		pm_power_off = NULL;
//	}
//#endif
//
//
	ExFreePoolWithTag(system, 'IPCA');

	return 0;
}