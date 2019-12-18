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
 scalar_t__ ACPI_STATE_S1 ; 
 scalar_t__ ACPI_STATE_S4 ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_save_state_disk () ; 

ACPI_STATUS
acpi_system_save_state(
	UINT32			state)
{
	int			error = 0;

	/* Send notification to devices that they will be suspended.
	 * If any device or driver cannot make the transition, either up
	 * or down, we'll get an error back.
	 */
	/*if (state > ACPI_STATE_S1) {
		error = pm_send_all(PM_SAVE_STATE, (void *)3);
		if (error)
			return AE_ERROR;
	}*/

	//if (state <= ACPI_STATE_S5) {
	//	/* Tell devices to stop I/O and actually save their state.
	//	 * It is theoretically possible that something could fail,
	//	 * so handle that gracefully..
	//	 */
	//	if (state > ACPI_STATE_S1 && state != ACPI_STATE_S5) {
	//		error = pm_send_all(PM_SUSPEND, (void *)3);
	//		if (error) {
	//			/* Tell devices to restore state if they have
	//			 * it saved and to start taking I/O requests.
	//			 */
	//			pm_send_all(PM_RESUME, (void *)0);
	//			return error;
	//		}
	//	}
		
		/* flush caches */
		ACPI_FLUSH_CPU_CACHE();

		/* Do arch specific saving of state. */
		if (state > ACPI_STATE_S1) {
			error = 0;//acpi_save_state_mem();

			/* TBD: if no s4bios, write codes for
			 * acpi_save_state_disk()...
			 */
#if 0
			if (!error && (state == ACPI_STATE_S4))
				error = acpi_save_state_disk();
#endif
			/*if (error) {
				pm_send_all(PM_RESUME, (void *)0);
				return error;
			}*/
		}
	//}
	/* disable interrupts
	 * Note that acpi_suspend -- our caller -- will do this once we return.
	 * But, we want it done early, so we don't get any surprises during
	 * the device suspend sequence.
	 */
	//ACPI_DISABLE_IRQS();

	/* Unconditionally turn off devices.
	 * Obvious if we enter a sleep state.
	 * If entering S5 (soft off), this should put devices in a
	 * quiescent state.
	 */

	//if (state > ACPI_STATE_S1) {
	//	error = pm_send_all(PM_SUSPEND, (void *)3);

	//	/* We're pretty screwed if we got an error from this.
	//	 * We try to recover by simply calling our own restore_state
	//	 * function; see above for definition.
	//	 *
	//	 * If it's S5 though, go through with it anyway..
	//	 */
	//	if (error && state != ACPI_STATE_S5)
	//		acpi_system_restore_state(state);
	//}
	return error ? AE_ERROR : AE_OK;
}