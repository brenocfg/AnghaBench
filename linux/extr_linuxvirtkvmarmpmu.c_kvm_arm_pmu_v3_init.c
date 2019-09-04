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
struct TYPE_4__ {int created; int /*<<< orphan*/  irq_num; } ;
struct TYPE_3__ {TYPE_2__ pmu; int /*<<< orphan*/  features; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  KVM_ARM_VCPU_PMU_V3 ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arm_pmu_irq_initialized (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arm_support_pmu_v3 () ; 
 int kvm_vgic_set_owner (struct kvm_vcpu*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_arm_pmu_v3_init(struct kvm_vcpu *vcpu)
{
	if (!kvm_arm_support_pmu_v3())
		return -ENODEV;

	if (!test_bit(KVM_ARM_VCPU_PMU_V3, vcpu->arch.features))
		return -ENXIO;

	if (vcpu->arch.pmu.created)
		return -EBUSY;

	if (irqchip_in_kernel(vcpu->kvm)) {
		int ret;

		/*
		 * If using the PMU with an in-kernel virtual GIC
		 * implementation, we require the GIC to be already
		 * initialized when initializing the PMU.
		 */
		if (!vgic_initialized(vcpu->kvm))
			return -ENODEV;

		if (!kvm_arm_pmu_irq_initialized(vcpu))
			return -ENXIO;

		ret = kvm_vgic_set_owner(vcpu, vcpu->arch.pmu.irq_num,
					 &vcpu->arch.pmu);
		if (ret)
			return ret;
	}

	vcpu->arch.pmu.created = true;
	return 0;
}