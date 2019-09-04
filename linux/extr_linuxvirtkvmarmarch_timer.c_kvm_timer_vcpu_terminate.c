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
struct arch_timer_cpu {int /*<<< orphan*/  phys_timer; int /*<<< orphan*/  expired; int /*<<< orphan*/  bg_timer; } ;
struct TYPE_3__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vgic_unmap_phys_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_terminate(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);

	soft_timer_cancel(&timer->bg_timer, &timer->expired);
	soft_timer_cancel(&timer->phys_timer, NULL);
	kvm_vgic_unmap_phys_irq(vcpu, vtimer->irq.irq);
}