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
struct TYPE_3__ {scalar_t__ level; } ;
struct arch_timer_context {TYPE_1__ irq; int /*<<< orphan*/  cntvoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_gic_active_state ; 
 scalar_t__ kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_load_gic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_load_nogic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  phys_timer_emulate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_cntvoff (int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vtimer_restore_state (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_load(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	if (unlikely(!timer->enabled))
		return;

	if (static_branch_likely(&has_gic_active_state))
		kvm_timer_vcpu_load_gic(vcpu);
	else
		kvm_timer_vcpu_load_nogic(vcpu);

	set_cntvoff(vtimer->cntvoff);

	vtimer_restore_state(vcpu);

	/* Set the background timer for the physical timer emulation. */
	phys_timer_emulate(vcpu);

	/* If the timer fired while we weren't running, inject it now */
	if (kvm_timer_should_fire(ptimer) != ptimer->irq.level)
		kvm_timer_update_irq(vcpu, !ptimer->irq.level, ptimer);
}