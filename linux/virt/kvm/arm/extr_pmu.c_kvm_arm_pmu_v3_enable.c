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
struct TYPE_3__ {int irq_num; int ready; int /*<<< orphan*/  created; } ;
struct TYPE_4__ {TYPE_1__ pmu; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  irq_is_ppi (int) ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_arm_pmu_irq_initialized (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_vcpu_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_valid_spi (int /*<<< orphan*/ ,int) ; 

int kvm_arm_pmu_v3_enable(struct kvm_vcpu *vcpu)
{
	if (!vcpu->arch.pmu.created)
		return 0;

	/*
	 * A valid interrupt configuration for the PMU is either to have a
	 * properly configured interrupt number and using an in-kernel
	 * irqchip, or to not have an in-kernel GIC and not set an IRQ.
	 */
	if (irqchip_in_kernel(vcpu->kvm)) {
		int irq = vcpu->arch.pmu.irq_num;
		if (!kvm_arm_pmu_irq_initialized(vcpu))
			return -EINVAL;

		/*
		 * If we are using an in-kernel vgic, at this point we know
		 * the vgic will be initialized, so we can check the PMU irq
		 * number against the dimensions of the vgic and make sure
		 * it's valid.
		 */
		if (!irq_is_ppi(irq) && !vgic_valid_spi(vcpu->kvm, irq))
			return -EINVAL;
	} else if (kvm_arm_pmu_irq_initialized(vcpu)) {
		   return -EINVAL;
	}

	kvm_pmu_vcpu_reset(vcpu);
	vcpu->arch.pmu.ready = true;

	return 0;
}