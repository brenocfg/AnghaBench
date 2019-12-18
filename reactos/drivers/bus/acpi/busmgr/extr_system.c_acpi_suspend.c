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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FLUSH_CPU_CACHE () ; 
 scalar_t__ ACPI_STATE_S5 ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEnterSleepState (scalar_t__) ; 
 int /*<<< orphan*/  AcpiEnterSleepStatePrep (scalar_t__) ; 
 int /*<<< orphan*/  AcpiLeaveSleepState (scalar_t__) ; 
 int /*<<< orphan*/  AcpiSetFirmwareWakingVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _disable () ; 
 int /*<<< orphan*/  _enable () ; 
 int /*<<< orphan*/  acpi_system_restore_state (scalar_t__) ; 
 int /*<<< orphan*/  acpi_system_suspend (scalar_t__) ; 

ACPI_STATUS
acpi_suspend (
	UINT32			state)
{
	ACPI_STATUS status;

	/* only support S1 and S5 on kernel 2.4 */
	//if (state != ACPI_STATE_S1 && state != ACPI_STATE_S4
	//    && state != ACPI_STATE_S5)
	//	return AE_ERROR;


	//if (ACPI_STATE_S4 == state) {
	//	/* For s4bios, we need a wakeup address. */
	//	if (1 == AcpiGbl_FACS->S4bios_f &&
	//	    0 != AcpiGbl_FADT->smi_cmd) {
	//		if (!acpi_wakeup_address)
	//			return AE_ERROR;
	//		AcpiSetFirmwareWakingVector((acpi_physical_address) acpi_wakeup_address);
	//	} else
	//		/* We don't support S4 under 2.4.  Give up */
	//		return AE_ERROR;
	//}
	AcpiEnterSleepStatePrep(state);

	status = AcpiEnterSleepState(state);
	if (!ACPI_SUCCESS(status) && state != ACPI_STATE_S5)
		return status;

	/* disable interrupts and flush caches */
	_disable();
	ACPI_FLUSH_CPU_CACHE();

	/* perform OS-specific sleep actions */
	status = acpi_system_suspend(state);

	/* Even if we failed to go to sleep, all of the devices are in an suspended
	 * mode. So, we run these unconditionally to make sure we have a usable system
	 * no matter what.
	 */
	AcpiLeaveSleepState(state);
	acpi_system_restore_state(state);

	/* make sure interrupts are enabled */
	_enable();

	/* reset firmware waking vector */
	AcpiSetFirmwareWakingVector(0, 0);

	return status;
}