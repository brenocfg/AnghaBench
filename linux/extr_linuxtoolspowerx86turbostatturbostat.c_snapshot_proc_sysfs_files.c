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

/* Variables and functions */
 int /*<<< orphan*/  BIC_CPU_LPI ; 
 int /*<<< orphan*/  BIC_GFXMHz ; 
 int /*<<< orphan*/  BIC_GFX_rc6 ; 
 int /*<<< orphan*/  BIC_IRQ ; 
 int /*<<< orphan*/  BIC_SYS_LPI ; 
 scalar_t__ DO_BIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapshot_cpu_lpi_us () ; 
 int /*<<< orphan*/  snapshot_gfx_mhz () ; 
 int /*<<< orphan*/  snapshot_gfx_rc6_ms () ; 
 scalar_t__ snapshot_proc_interrupts () ; 
 int /*<<< orphan*/  snapshot_sys_lpi_us () ; 

int snapshot_proc_sysfs_files(void)
{
	if (DO_BIC(BIC_IRQ))
		if (snapshot_proc_interrupts())
			return 1;

	if (DO_BIC(BIC_GFX_rc6))
		snapshot_gfx_rc6_ms();

	if (DO_BIC(BIC_GFXMHz))
		snapshot_gfx_mhz();

	if (DO_BIC(BIC_CPU_LPI))
		snapshot_cpu_lpi_us();

	if (DO_BIC(BIC_SYS_LPI))
		snapshot_sys_lpi_us();

	return 0;
}