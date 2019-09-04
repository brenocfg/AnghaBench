#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int wireless; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACER_CAP_BLUETOOTH ; 
 int /*<<< orphan*/  ACER_CAP_THREEG ; 
 int /*<<< orphan*/  ACER_CAP_WIRELESS ; 
 int /*<<< orphan*/  ACER_WMID3_GDS_THREEG ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  WMID_GUID3 ; 
 int /*<<< orphan*/  acer_rfkill_work ; 
 int /*<<< orphan*/  bluetooth_rfkill ; 
 int /*<<< orphan*/  get_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ has_cap (int /*<<< orphan*/ ) ; 
 TYPE_1__* quirks ; 
 int /*<<< orphan*/  rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threeg_rfkill ; 
 int /*<<< orphan*/  wireless_rfkill ; 
 scalar_t__ wmi_has_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acer_rfkill_update(struct work_struct *ignored)
{
	u32 state;
	acpi_status status;

	if (has_cap(ACER_CAP_WIRELESS)) {
		status = get_u32(&state, ACER_CAP_WIRELESS);
		if (ACPI_SUCCESS(status)) {
			if (quirks->wireless == 3)
				rfkill_set_hw_state(wireless_rfkill, !state);
			else
				rfkill_set_sw_state(wireless_rfkill, !state);
		}
	}

	if (has_cap(ACER_CAP_BLUETOOTH)) {
		status = get_u32(&state, ACER_CAP_BLUETOOTH);
		if (ACPI_SUCCESS(status))
			rfkill_set_sw_state(bluetooth_rfkill, !state);
	}

	if (has_cap(ACER_CAP_THREEG) && wmi_has_guid(WMID_GUID3)) {
		status = get_u32(&state, ACER_WMID3_GDS_THREEG);
		if (ACPI_SUCCESS(status))
			rfkill_set_sw_state(threeg_rfkill, !state);
	}

	schedule_delayed_work(&acer_rfkill_work, round_jiffies_relative(HZ));
}