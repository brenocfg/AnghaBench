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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int level; int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_1__ irq; } ;

/* Variables and functions */
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int kvm_vgic_map_is_active (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_vtimer_irq_phys_active (struct kvm_vcpu*,int) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_timer_vcpu_load_gic(struct kvm_vcpu *vcpu)
{
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	bool phys_active;

	if (irqchip_in_kernel(vcpu->kvm))
		phys_active = kvm_vgic_map_is_active(vcpu, vtimer->irq.irq);
	else
		phys_active = vtimer->irq.level;
	set_vtimer_irq_phys_active(vcpu, phys_active);
}