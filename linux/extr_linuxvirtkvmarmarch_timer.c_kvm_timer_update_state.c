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
struct arch_timer_cpu {int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int level; } ;
struct arch_timer_context {TYPE_1__ irq; } ;

/* Variables and functions */
 int kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  phys_timer_emulate (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_timer_update_state(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);
	bool level;

	if (unlikely(!timer->enabled))
		return;

	/*
	 * The vtimer virtual interrupt is a 'mapped' interrupt, meaning part
	 * of its lifecycle is offloaded to the hardware, and we therefore may
	 * not have lowered the irq.level value before having to signal a new
	 * interrupt, but have to signal an interrupt every time the level is
	 * asserted.
	 */
	level = kvm_timer_should_fire(vtimer);
	kvm_timer_update_irq(vcpu, level, vtimer);

	phys_timer_emulate(vcpu);

	if (kvm_timer_should_fire(ptimer) != ptimer->irq.level)
		kvm_timer_update_irq(vcpu, !ptimer->irq.level, ptimer);
}