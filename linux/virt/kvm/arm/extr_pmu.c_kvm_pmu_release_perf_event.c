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
struct kvm_pmc {int /*<<< orphan*/ * perf_event; } ;

/* Variables and functions */
 struct kvm_pmc* kvm_pmu_get_canonical_pmc (struct kvm_pmc*) ; 
 int /*<<< orphan*/  perf_event_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_release_kernel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_pmu_release_perf_event(struct kvm_pmc *pmc)
{
	pmc = kvm_pmu_get_canonical_pmc(pmc);
	if (pmc->perf_event) {
		perf_event_disable(pmc->perf_event);
		perf_event_release_kernel(pmc->perf_event);
		pmc->perf_event = NULL;
	}
}