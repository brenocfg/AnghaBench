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
struct TYPE_4__ {int /*<<< orphan*/  ap_list_lock; int /*<<< orphan*/  ap_list_head; } ;
struct TYPE_3__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SPINLOCK_BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ can_access_vgic_from_kernel () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_flush_lr_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_restore_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_supports_direct_msis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_v4_flush_hwstate (struct kvm_vcpu*) ; 

void kvm_vgic_flush_hwstate(struct kvm_vcpu *vcpu)
{
	WARN_ON(vgic_v4_flush_hwstate(vcpu));

	/*
	 * If there are no virtual interrupts active or pending for this
	 * VCPU, then there is no work to do and we can bail out without
	 * taking any lock.  There is a potential race with someone injecting
	 * interrupts to the VCPU, but it is a benign race as the VCPU will
	 * either observe the new interrupt before or after doing this check,
	 * and introducing additional synchronization mechanism doesn't change
	 * this.
	 *
	 * Note that we still need to go through the whole thing if anything
	 * can be directly injected (GICv4).
	 */
	if (list_empty(&vcpu->arch.vgic_cpu.ap_list_head) &&
	    !vgic_supports_direct_msis(vcpu->kvm))
		return;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

	if (!list_empty(&vcpu->arch.vgic_cpu.ap_list_head)) {
		raw_spin_lock(&vcpu->arch.vgic_cpu.ap_list_lock);
		vgic_flush_lr_state(vcpu);
		raw_spin_unlock(&vcpu->arch.vgic_cpu.ap_list_lock);
	}

	if (can_access_vgic_from_kernel())
		vgic_restore_state(vcpu);
}