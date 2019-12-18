#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct arch_timer_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_gic_active_state ; 
 int /*<<< orphan*/  host_vtimer_irq ; 
 int /*<<< orphan*/  host_vtimer_irq_flags ; 
 int /*<<< orphan*/  kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  set_timer_irq_phys_active (struct arch_timer_context*,int) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void unmask_vtimer_irq_user(struct kvm_vcpu *vcpu)
{
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);

	if (!kvm_timer_should_fire(vtimer)) {
		kvm_timer_update_irq(vcpu, false, vtimer);
		if (static_branch_likely(&has_gic_active_state))
			set_timer_irq_phys_active(vtimer, false);
		else
			enable_percpu_irq(host_vtimer_irq, host_vtimer_irq_flags);
	}
}