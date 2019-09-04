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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
struct arch_timer_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ ULLONG_MAX ; 
 scalar_t__ kvm_timer_compute_delta (struct arch_timer_context*) ; 
 scalar_t__ kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 kvm_timer_earliest_exp(struct kvm_vcpu *vcpu)
{
	u64 min_virt = ULLONG_MAX, min_phys = ULLONG_MAX;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	if (kvm_timer_irq_can_fire(vtimer))
		min_virt = kvm_timer_compute_delta(vtimer);

	if (kvm_timer_irq_can_fire(ptimer))
		min_phys = kvm_timer_compute_delta(ptimer);

	/* If none of timers can fire, then return 0 */
	if ((min_virt == ULLONG_MAX) && (min_phys == ULLONG_MAX))
		return 0;

	return min(min_virt, min_phys);
}