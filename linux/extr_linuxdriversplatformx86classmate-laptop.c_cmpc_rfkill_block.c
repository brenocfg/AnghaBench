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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  void* acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  cmpc_get_rfkill_wlan (void*,unsigned long long*) ; 
 int /*<<< orphan*/  cmpc_set_rfkill_wlan (void*,unsigned long long) ; 

__attribute__((used)) static int cmpc_rfkill_block(void *data, bool blocked)
{
	acpi_status status;
	acpi_handle handle;
	unsigned long long state;
	bool is_blocked;

	handle = data;
	status = cmpc_get_rfkill_wlan(handle, &state);
	if (ACPI_FAILURE(status))
		return -ENODEV;
	/* Check if we really need to call cmpc_set_rfkill_wlan */
	is_blocked = state & 1 ? false : true;
	if (is_blocked != blocked) {
		state = blocked ? 0 : 1;
		status = cmpc_set_rfkill_wlan(handle, state);
		if (ACPI_FAILURE(status))
			return -ENODEV;
	}
	return 0;
}