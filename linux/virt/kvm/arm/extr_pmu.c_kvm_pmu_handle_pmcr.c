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
 int ARMV8_PMU_CYCLE_IDX ; 
 int ARMV8_PMU_PMCR_C ; 
 int ARMV8_PMU_PMCR_E ; 
 int ARMV8_PMU_PMCR_P ; 
 int /*<<< orphan*/  PMCNTENSET_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pmu_disable_counter_mask (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_pmu_enable_counter_mask (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_pmu_set_counter_value (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int kvm_pmu_valid_counter_mask (struct kvm_vcpu*) ; 

void kvm_pmu_handle_pmcr(struct kvm_vcpu *vcpu, u64 val)
{
	u64 mask;
	int i;

	mask = kvm_pmu_valid_counter_mask(vcpu);
	if (val & ARMV8_PMU_PMCR_E) {
		kvm_pmu_enable_counter_mask(vcpu,
		       __vcpu_sys_reg(vcpu, PMCNTENSET_EL0) & mask);
	} else {
		kvm_pmu_disable_counter_mask(vcpu, mask);
	}

	if (val & ARMV8_PMU_PMCR_C)
		kvm_pmu_set_counter_value(vcpu, ARMV8_PMU_CYCLE_IDX, 0);

	if (val & ARMV8_PMU_PMCR_P) {
		for (i = 0; i < ARMV8_PMU_CYCLE_IDX; i++)
			kvm_pmu_set_counter_value(vcpu, i, 0);
	}
}