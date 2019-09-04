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
struct arch_timer_cpu {int /*<<< orphan*/  bg_timer; } ;
struct TYPE_2__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct arch_timer_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_timer_earliest_exp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 scalar_t__ kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  soft_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vtimer_save_state (struct kvm_vcpu*) ; 

void kvm_timer_schedule(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	vtimer_save_state(vcpu);

	/*
	 * No need to schedule a background timer if any guest timer has
	 * already expired, because kvm_vcpu_block will return before putting
	 * the thread to sleep.
	 */
	if (kvm_timer_should_fire(vtimer) || kvm_timer_should_fire(ptimer))
		return;

	/*
	 * If both timers are not capable of raising interrupts (disabled or
	 * masked), then there's no more work for us to do.
	 */
	if (!kvm_timer_irq_can_fire(vtimer) && !kvm_timer_irq_can_fire(ptimer))
		return;

	/*
	 * The guest timers have not yet expired, schedule a background timer.
	 * Set the earliest expiration time among the guest timers.
	 */
	soft_timer_start(&timer->bg_timer, kvm_timer_earliest_exp(vcpu));
}