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
struct arch_timer_cpu {int /*<<< orphan*/  phys_timer; } ;
struct TYPE_2__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct arch_timer_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_timer_compute_delta (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 scalar_t__ kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void phys_timer_emulate(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	/*
	 * If the timer can fire now, we don't need to have a soft timer
	 * scheduled for the future.  If the timer cannot fire at all,
	 * then we also don't need a soft timer.
	 */
	if (kvm_timer_should_fire(ptimer) || !kvm_timer_irq_can_fire(ptimer)) {
		soft_timer_cancel(&timer->phys_timer, NULL);
		return;
	}

	soft_timer_start(&timer->phys_timer, kvm_timer_compute_delta(ptimer));
}