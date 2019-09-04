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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_PMU_CYCLE_IDX ; 
 int ARMV8_PMU_PMCR_N_MASK ; 
 int ARMV8_PMU_PMCR_N_SHIFT ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCR_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

u64 kvm_pmu_valid_counter_mask(struct kvm_vcpu *vcpu)
{
	u64 val = __vcpu_sys_reg(vcpu, PMCR_EL0) >> ARMV8_PMU_PMCR_N_SHIFT;

	val &= ARMV8_PMU_PMCR_N_MASK;
	if (val == 0)
		return BIT(ARMV8_PMU_CYCLE_IDX);
	else
		return GENMASK(val - 1, 0) | BIT(ARMV8_PMU_CYCLE_IDX);
}