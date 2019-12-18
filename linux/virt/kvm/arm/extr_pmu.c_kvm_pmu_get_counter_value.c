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
typedef  size_t u64 ;
struct kvm_pmu {struct kvm_pmc* pmc; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 size_t ARMV8_PMU_CYCLE_IDX ; 
 size_t kvm_pmu_get_pair_counter_value (struct kvm_vcpu*,struct kvm_pmc*) ; 
 scalar_t__ kvm_pmu_idx_is_high_counter (size_t) ; 
 scalar_t__ kvm_pmu_pmc_is_chained (struct kvm_pmc*) ; 
 size_t lower_32_bits (size_t) ; 
 size_t upper_32_bits (size_t) ; 

u64 kvm_pmu_get_counter_value(struct kvm_vcpu *vcpu, u64 select_idx)
{
	u64 counter;
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_pmc *pmc = &pmu->pmc[select_idx];

	counter = kvm_pmu_get_pair_counter_value(vcpu, pmc);

	if (kvm_pmu_pmc_is_chained(pmc) &&
	    kvm_pmu_idx_is_high_counter(select_idx))
		counter = upper_32_bits(counter);
	else if (select_idx != ARMV8_PMU_CYCLE_IDX)
		counter = lower_32_bits(counter);

	return counter;
}