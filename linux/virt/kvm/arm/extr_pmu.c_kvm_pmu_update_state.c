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
struct kvm_pmu {int irq_level; int /*<<< orphan*/  irq_num; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_pmu_v3_ready (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_overflow_status (struct kvm_vcpu*) ; 
 int kvm_vgic_inject_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct kvm_pmu*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_pmu_update_state(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	bool overflow;

	if (!kvm_arm_pmu_v3_ready(vcpu))
		return;

	overflow = !!kvm_pmu_overflow_status(vcpu);
	if (pmu->irq_level == overflow)
		return;

	pmu->irq_level = overflow;

	if (likely(irqchip_in_kernel(vcpu->kvm))) {
		int ret = kvm_vgic_inject_irq(vcpu->kvm, vcpu->vcpu_id,
					      pmu->irq_num, overflow, pmu);
		WARN_ON(ret);
	}
}