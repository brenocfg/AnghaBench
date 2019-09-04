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
struct rfkill {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  void* acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpc_get_rfkill_wlan (void*,unsigned long long*) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (struct rfkill*,int) ; 

__attribute__((used)) static void cmpc_rfkill_query(struct rfkill *rfkill, void *data)
{
	acpi_status status;
	acpi_handle handle;
	unsigned long long state;
	bool blocked;

	handle = data;
	status = cmpc_get_rfkill_wlan(handle, &state);
	if (ACPI_SUCCESS(status)) {
		blocked = state & 1 ? false : true;
		rfkill_set_sw_state(rfkill, blocked);
	}
}