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
struct vgic_irq {int pending_latch; int /*<<< orphan*/  active; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vgic_irq_set_phys_active (struct vgic_irq*,int) ; 
 int /*<<< orphan*/  vgic_irq_set_phys_pending (struct vgic_irq*,int) ; 

__attribute__((used)) static void vgic_hw_irq_cpending(struct kvm_vcpu *vcpu, struct vgic_irq *irq,
				 bool is_uaccess)
{
	if (is_uaccess)
		return;

	irq->pending_latch = false;

	/*
	 * We don't want the guest to effectively mask the physical
	 * interrupt by doing a write to SPENDR followed by a write to
	 * CPENDR for HW interrupts, so we clear the active state on
	 * the physical side if the virtual interrupt is not active.
	 * This may lead to taking an additional interrupt on the
	 * host, but that should not be a problem as the worst that
	 * can happen is an additional vgic injection.  We also clear
	 * the pending state to maintain proper semantics for edge HW
	 * interrupts.
	 */
	vgic_irq_set_phys_pending(irq, false);
	if (!irq->active)
		vgic_irq_set_phys_active(irq, false);
}