#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chained; } ;
struct TYPE_4__ {TYPE_1__ pmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_pmc {int idx; } ;

/* Variables and functions */
 struct kvm_vcpu* kvm_pmc_to_vcpu (struct kvm_pmc*) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_pmu_pmc_is_chained(struct kvm_pmc *pmc)
{
	struct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);

	return test_bit(pmc->idx >> 1, vcpu->arch.pmu.chained);
}