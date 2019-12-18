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
struct kvm_pmc {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 scalar_t__ kvm_pmu_idx_is_high_counter (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_pmu_pmc_is_chained (struct kvm_pmc*) ; 

__attribute__((used)) static struct kvm_pmc *kvm_pmu_get_canonical_pmc(struct kvm_pmc *pmc)
{
	if (kvm_pmu_pmc_is_chained(pmc) &&
	    kvm_pmu_idx_is_high_counter(pmc->idx))
		return pmc - 1;

	return pmc;
}