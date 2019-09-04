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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int xen_acpi_notify_hypervisor_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int xen_acpi_notify_hypervisor_sleep(u8 sleep_state,
				     u32 pm1a_cnt, u32 pm1b_cnt)
{
	return xen_acpi_notify_hypervisor_state(sleep_state, pm1a_cnt,
						pm1b_cnt, false);
}