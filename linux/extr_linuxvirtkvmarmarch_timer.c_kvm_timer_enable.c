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
struct arch_timer_cpu {int enabled; } ;
struct TYPE_3__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_2__ irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  host_vtimer_irq ; 
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_timer_get_input_level ; 
 int /*<<< orphan*/  kvm_debug (char*) ; 
 int kvm_vgic_map_phys_irq (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_irqs_are_valid (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 

int kvm_timer_enable(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	int ret;

	if (timer->enabled)
		return 0;

	/* Without a VGIC we do not map virtual IRQs to physical IRQs */
	if (!irqchip_in_kernel(vcpu->kvm))
		goto no_vgic;

	if (!vgic_initialized(vcpu->kvm))
		return -ENODEV;

	if (!timer_irqs_are_valid(vcpu)) {
		kvm_debug("incorrectly configured timer irqs\n");
		return -EINVAL;
	}

	ret = kvm_vgic_map_phys_irq(vcpu, host_vtimer_irq, vtimer->irq.irq,
				    kvm_arch_timer_get_input_level);
	if (ret)
		return ret;

no_vgic:
	timer->enabled = 1;
	return 0;
}