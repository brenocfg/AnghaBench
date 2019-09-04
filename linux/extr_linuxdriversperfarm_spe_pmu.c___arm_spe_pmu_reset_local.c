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
 int /*<<< orphan*/  SYS_PMBPTR_EL1 ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1 ; 
 int /*<<< orphan*/  arm_spe_pmu_disable_and_drain_local () ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  write_sysreg_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __arm_spe_pmu_reset_local(void)
{
	/*
	 * This is probably overkill, as we have no idea where we're
	 * draining any buffered data to...
	 */
	arm_spe_pmu_disable_and_drain_local();

	/* Reset the buffer base pointer */
	write_sysreg_s(0, SYS_PMBPTR_EL1);
	isb();

	/* Clear any pending management interrupts */
	write_sysreg_s(0, SYS_PMBSR_EL1);
	isb();
}