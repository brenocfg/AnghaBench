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
struct kvm_pmu {struct kvm_pmc* pmc; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {int /*<<< orphan*/ * perf_event; } ;

/* Variables and functions */
 int ARMV8_PMU_MAX_COUNTERS ; 
 int /*<<< orphan*/  perf_event_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_release_kernel (int /*<<< orphan*/ *) ; 

void kvm_pmu_vcpu_destroy(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_pmu *pmu = &vcpu->arch.pmu;

	for (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++) {
		struct kvm_pmc *pmc = &pmu->pmc[i];

		if (pmc->perf_event) {
			perf_event_disable(pmc->perf_event);
			perf_event_release_kernel(pmc->perf_event);
			pmc->perf_event = NULL;
		}
	}
}