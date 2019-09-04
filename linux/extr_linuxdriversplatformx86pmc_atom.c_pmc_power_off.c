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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ PM1_CNT ; 
 int /*<<< orphan*/  SLEEP_ENABLE ; 
 int /*<<< orphan*/  SLEEP_TYPE_MASK ; 
 int /*<<< orphan*/  SLEEP_TYPE_S5 ; 
 scalar_t__ acpi_base_addr ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void pmc_power_off(void)
{
	u16	pm1_cnt_port;
	u32	pm1_cnt_value;

	pr_info("Preparing to enter system sleep state S5\n");

	pm1_cnt_port = acpi_base_addr + PM1_CNT;

	pm1_cnt_value = inl(pm1_cnt_port);
	pm1_cnt_value &= SLEEP_TYPE_MASK;
	pm1_cnt_value |= SLEEP_TYPE_S5;
	pm1_cnt_value |= SLEEP_ENABLE;

	outl(pm1_cnt_value, pm1_cnt_port);
}