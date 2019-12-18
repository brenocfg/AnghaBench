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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ level; } ;
struct arch_timer_context {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_vtimer_irq ; 
 int /*<<< orphan*/  host_vtimer_irq_flags ; 
 int /*<<< orphan*/  kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int /*<<< orphan*/ ,struct arch_timer_context*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_timer_vcpu_load_nogic(struct kvm_vcpu *vcpu)
{
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);

	/*
	 * Update the timer output so that it is likely to match the
	 * state we're about to restore. If the timer expires between
	 * this point and the register restoration, we'll take the
	 * interrupt anyway.
	 */
	kvm_timer_update_irq(vcpu, kvm_timer_should_fire(vtimer), vtimer);

	/*
	 * When using a userspace irqchip with the architected timers and a
	 * host interrupt controller that doesn't support an active state, we
	 * must still prevent continuously exiting from the guest, and
	 * therefore mask the physical interrupt by disabling it on the host
	 * interrupt controller when the virtual level is high, such that the
	 * guest can make forward progress.  Once we detect the output level
	 * being de-asserted, we unmask the interrupt again so that we exit
	 * from the guest when the timer fires.
	 */
	if (vtimer->irq.level)
		disable_percpu_irq(host_vtimer_irq);
	else
		enable_percpu_irq(host_vtimer_irq, host_vtimer_irq_flags);
}