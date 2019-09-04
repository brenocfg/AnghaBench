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
struct arch_timer_cpu {int /*<<< orphan*/  phys_timer; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_vhe () ; 
 int /*<<< orphan*/  set_cntvoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vtimer_save_state (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_put(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;

	if (unlikely(!timer->enabled))
		return;

	vtimer_save_state(vcpu);

	/*
	 * Cancel the physical timer emulation, because the only case where we
	 * need it after a vcpu_put is in the context of a sleeping VCPU, and
	 * in that case we already factor in the deadline for the physical
	 * timer when scheduling the bg_timer.
	 *
	 * In any case, we re-schedule the hrtimer for the physical timer when
	 * coming back to the VCPU thread in kvm_timer_vcpu_load().
	 */
	soft_timer_cancel(&timer->phys_timer, NULL);

	/*
	 * The kernel may decide to run userspace after calling vcpu_put, so
	 * we reset cntvoff to 0 to ensure a consistent read between user
	 * accesses to the virtual counter and kernel access to the physical
	 * counter of non-VHE case. For VHE, the virtual counter uses a fixed
	 * virtual offset of zero, so no need to zero CNTVOFF_EL2 register.
	 */
	if (!has_vhe())
		set_cntvoff(0);
}