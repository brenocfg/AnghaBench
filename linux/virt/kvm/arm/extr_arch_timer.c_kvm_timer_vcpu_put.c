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
struct timer_map {TYPE_1__* emul_ptimer; scalar_t__ direct_ptimer; scalar_t__ direct_vtimer; } ;
struct kvm_vcpu {int dummy; } ;
struct arch_timer_cpu {int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_wq (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_blocking (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_cntvoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ swait_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_save_state (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_put(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);
	struct timer_map map;

	if (unlikely(!timer->enabled))
		return;

	get_timer_map(vcpu, &map);

	timer_save_state(map.direct_vtimer);
	if (map.direct_ptimer)
		timer_save_state(map.direct_ptimer);

	/*
	 * Cancel soft timer emulation, because the only case where we
	 * need it after a vcpu_put is in the context of a sleeping VCPU, and
	 * in that case we already factor in the deadline for the physical
	 * timer when scheduling the bg_timer.
	 *
	 * In any case, we re-schedule the hrtimer for the physical timer when
	 * coming back to the VCPU thread in kvm_timer_vcpu_load().
	 */
	if (map.emul_ptimer)
		soft_timer_cancel(&map.emul_ptimer->hrtimer);

	if (swait_active(kvm_arch_vcpu_wq(vcpu)))
		kvm_timer_blocking(vcpu);

	/*
	 * The kernel may decide to run userspace after calling vcpu_put, so
	 * we reset cntvoff to 0 to ensure a consistent read between user
	 * accesses to the virtual counter and kernel access to the physical
	 * counter of non-VHE case. For VHE, the virtual counter uses a fixed
	 * virtual offset of zero, so no need to zero CNTVOFF_EL2 register.
	 */
	set_cntvoff(0);
}