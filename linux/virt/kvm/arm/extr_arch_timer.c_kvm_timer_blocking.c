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
struct timer_map {int /*<<< orphan*/  emul_ptimer; int /*<<< orphan*/  direct_ptimer; int /*<<< orphan*/  direct_vtimer; } ;
struct kvm_vcpu {int dummy; } ;
struct arch_timer_cpu {int /*<<< orphan*/  bg_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 int /*<<< orphan*/  kvm_timer_earliest_exp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_timer_blocking(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);
	struct timer_map map;

	get_timer_map(vcpu, &map);

	/*
	 * If no timers are capable of raising interrupts (disabled or
	 * masked), then there's no more work for us to do.
	 */
	if (!kvm_timer_irq_can_fire(map.direct_vtimer) &&
	    !kvm_timer_irq_can_fire(map.direct_ptimer) &&
	    !kvm_timer_irq_can_fire(map.emul_ptimer))
		return;

	/*
	 * At least one guest time will expire. Schedule a background timer.
	 * Set the earliest expiration time among the guest timers.
	 */
	soft_timer_start(&timer->bg_timer, kvm_timer_earliest_exp(vcpu));
}