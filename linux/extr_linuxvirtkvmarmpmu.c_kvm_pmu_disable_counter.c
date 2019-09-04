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
typedef  int u64 ;
struct kvm_pmu {struct kvm_pmc* pmc; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {scalar_t__ perf_event; } ;

/* Variables and functions */
 int ARMV8_PMU_MAX_COUNTERS ; 
 int BIT (int) ; 
 int /*<<< orphan*/  perf_event_disable (scalar_t__) ; 

void kvm_pmu_disable_counter(struct kvm_vcpu *vcpu, u64 val)
{
	int i;
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_pmc *pmc;

	if (!val)
		return;

	for (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++) {
		if (!(val & BIT(i)))
			continue;

		pmc = &pmu->pmc[i];
		if (pmc->perf_event)
			perf_event_disable(pmc->perf_event);
	}
}