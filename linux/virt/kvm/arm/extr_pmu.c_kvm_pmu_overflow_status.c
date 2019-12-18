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
 int ARMV8_PMU_PMCR_E ; 
 int /*<<< orphan*/  PMCNTENSET_EL0 ; 
 int /*<<< orphan*/  PMCR_EL0 ; 
 int /*<<< orphan*/  PMINTENSET_EL1 ; 
 int /*<<< orphan*/  PMOVSSET_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_pmu_valid_counter_mask (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 kvm_pmu_overflow_status(struct kvm_vcpu *vcpu)
{
	u64 reg = 0;

	if ((__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_E)) {
		reg = __vcpu_sys_reg(vcpu, PMOVSSET_EL0);
		reg &= __vcpu_sys_reg(vcpu, PMCNTENSET_EL0);
		reg &= __vcpu_sys_reg(vcpu, PMINTENSET_EL1);
		reg &= kvm_pmu_valid_counter_mask(vcpu);
	}

	return reg;
}