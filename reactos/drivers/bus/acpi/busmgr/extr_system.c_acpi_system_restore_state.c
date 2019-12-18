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
 scalar_t__ ACPI_STATE_S1 ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  KeStallExecutionProcessor (int) ; 

ACPI_STATUS
acpi_system_restore_state(
	UINT32			state)
{
	/* 
	 * We should only be here if we're coming back from STR or STD.
	 * And, in the case of the latter, the memory image should have already
	 * been loaded from disk.
	 */
	if (state > ACPI_STATE_S1) {
		//acpi_restore_state_mem();

		/* Do _early_ resume for irqs.  Required by
		 * ACPI specs.
		 */
		/* TBD: call arch dependant reinitialization of the 
		 * interrupts.
		 */
#ifdef _X86_
		//init_8259A(0);
#endif
		/* wait for power to come back */
		KeStallExecutionProcessor(100);

	}

	/* Be really sure that irqs are disabled. */
	//ACPI_DISABLE_IRQS();

	/* Wait a little again, just in case... */
	KeStallExecutionProcessor(10);

	/* enable interrupts once again */
	//ACPI_ENABLE_IRQS();

	/* turn all the devices back on */
	//if (state > ACPI_STATE_S1)
		//pm_send_all(PM_RESUME, (void *)0);

	return AE_OK;
}