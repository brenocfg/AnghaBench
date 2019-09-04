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
struct kvm_pmc {size_t bitmask; scalar_t__ perf_event; } ;

/* Variables and functions */
 size_t ARMV8_PMU_CYCLE_IDX ; 
 size_t PMCCNTR_EL0 ; 
 size_t PMEVCNTR0_EL0 ; 
 size_t __vcpu_sys_reg (struct kvm_vcpu*,size_t) ; 
 scalar_t__ perf_event_read_value (scalar_t__,size_t*,size_t*) ; 

u64 kvm_pmu_get_counter_value(struct kvm_vcpu *vcpu, u64 select_idx)
{
	u64 counter, reg, enabled, running;
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_pmc *pmc = &pmu->pmc[select_idx];

	reg = (select_idx == ARMV8_PMU_CYCLE_IDX)
	      ? PMCCNTR_EL0 : PMEVCNTR0_EL0 + select_idx;
	counter = __vcpu_sys_reg(vcpu, reg);

	/* The real counter value is equal to the value of counter register plus
	 * the value perf event counts.
	 */
	if (pmc->perf_event)
		counter += perf_event_read_value(pmc->perf_event, &enabled,
						 &running);

	return counter & pmc->bitmask;
}