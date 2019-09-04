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
 int /*<<< orphan*/  L2PMCNTENCLR ; 
 int /*<<< orphan*/  L2PMCR ; 
 int /*<<< orphan*/  L2PMCR_RESET_ALL ; 
 int /*<<< orphan*/  L2PMINTENCLR ; 
 int /*<<< orphan*/  L2PMOVSCLR ; 
 int /*<<< orphan*/  l2_counter_present_mask ; 
 int /*<<< orphan*/  set_l2_indirect_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cluster_pmu_reset(void)
{
	/* Reset all counters */
	set_l2_indirect_reg(L2PMCR, L2PMCR_RESET_ALL);
	set_l2_indirect_reg(L2PMCNTENCLR, l2_counter_present_mask);
	set_l2_indirect_reg(L2PMINTENCLR, l2_counter_present_mask);
	set_l2_indirect_reg(L2PMOVSCLR, l2_counter_present_mask);
}