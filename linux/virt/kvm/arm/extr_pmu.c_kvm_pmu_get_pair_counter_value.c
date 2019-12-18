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
struct kvm_pmc {int idx; scalar_t__ perf_event; } ;

/* Variables and functions */
 scalar_t__ ARMV8_PMU_CYCLE_IDX ; 
 int PMCCNTR_EL0 ; 
 int PMEVCNTR0_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int) ; 
 struct kvm_pmc* kvm_pmu_get_canonical_pmc (struct kvm_pmc*) ; 
 scalar_t__ kvm_pmu_pmc_is_chained (struct kvm_pmc*) ; 
 int lower_32_bits (int) ; 
 scalar_t__ perf_event_read_value (scalar_t__,int*,int*) ; 

__attribute__((used)) static u64 kvm_pmu_get_pair_counter_value(struct kvm_vcpu *vcpu,
					  struct kvm_pmc *pmc)
{
	u64 counter, counter_high, reg, enabled, running;

	if (kvm_pmu_pmc_is_chained(pmc)) {
		pmc = kvm_pmu_get_canonical_pmc(pmc);
		reg = PMEVCNTR0_EL0 + pmc->idx;

		counter = __vcpu_sys_reg(vcpu, reg);
		counter_high = __vcpu_sys_reg(vcpu, reg + 1);

		counter = lower_32_bits(counter) | (counter_high << 32);
	} else {
		reg = (pmc->idx == ARMV8_PMU_CYCLE_IDX)
		      ? PMCCNTR_EL0 : PMEVCNTR0_EL0 + pmc->idx;
		counter = __vcpu_sys_reg(vcpu, reg);
	}

	/*
	 * The real counter value is equal to the value of counter register plus
	 * the value perf event counts.
	 */
	if (pmc->perf_event)
		counter += perf_event_read_value(pmc->perf_event, &enabled,
						 &running);

	return counter;
}