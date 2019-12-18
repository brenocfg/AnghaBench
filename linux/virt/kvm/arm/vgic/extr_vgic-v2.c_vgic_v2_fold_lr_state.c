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
typedef  int u32 ;
struct vgic_v2_cpu_if {int* vgic_lr; int /*<<< orphan*/  vgic_hcr; } ;
struct vgic_irq {int active; int active_source; scalar_t__ config; int pending_latch; int source; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  line_level; } ;
struct vgic_cpu {int used_lrs; struct vgic_v2_cpu_if vgic_v2; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SPINLOCK_BUG_ON (int) ; 
 int /*<<< orphan*/  GICH_HCR_UIE ; 
 int GICH_LR_ACTIVE_BIT ; 
 int GICH_LR_PENDING_BIT ; 
 int GICH_LR_PHYSID_CPUID ; 
 int GICH_LR_PHYSID_CPUID_SHIFT ; 
 int GICH_LR_STATE ; 
 int GICH_LR_VIRTUALID ; 
 scalar_t__ VGIC_CONFIG_EDGE ; 
 scalar_t__ VGIC_CONFIG_LEVEL ; 
 int VGIC_NR_PRIVATE_IRQS ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kvm_notify_acked_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lr_signals_eoi_mi (int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vgic_get_phys_line_level (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_mapped_level (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_sgi (int) ; 
 int /*<<< orphan*/  vgic_irq_set_phys_active (struct vgic_irq*,int) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 
 scalar_t__ vgic_valid_spi (int /*<<< orphan*/ ,int) ; 

void vgic_v2_fold_lr_state(struct kvm_vcpu *vcpu)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	struct vgic_v2_cpu_if *cpuif = &vgic_cpu->vgic_v2;
	int lr;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

	cpuif->vgic_hcr &= ~GICH_HCR_UIE;

	for (lr = 0; lr < vgic_cpu->used_lrs; lr++) {
		u32 val = cpuif->vgic_lr[lr];
		u32 cpuid, intid = val & GICH_LR_VIRTUALID;
		struct vgic_irq *irq;

		/* Extract the source vCPU id from the LR */
		cpuid = val & GICH_LR_PHYSID_CPUID;
		cpuid >>= GICH_LR_PHYSID_CPUID_SHIFT;
		cpuid &= 7;

		/* Notify fds when the guest EOI'ed a level-triggered SPI */
		if (lr_signals_eoi_mi(val) && vgic_valid_spi(vcpu->kvm, intid))
			kvm_notify_acked_irq(vcpu->kvm, 0,
					     intid - VGIC_NR_PRIVATE_IRQS);

		irq = vgic_get_irq(vcpu->kvm, vcpu, intid);

		raw_spin_lock(&irq->irq_lock);

		/* Always preserve the active bit */
		irq->active = !!(val & GICH_LR_ACTIVE_BIT);

		if (irq->active && vgic_irq_is_sgi(intid))
			irq->active_source = cpuid;

		/* Edge is the only case where we preserve the pending bit */
		if (irq->config == VGIC_CONFIG_EDGE &&
		    (val & GICH_LR_PENDING_BIT)) {
			irq->pending_latch = true;

			if (vgic_irq_is_sgi(intid))
				irq->source |= (1 << cpuid);
		}

		/*
		 * Clear soft pending state when level irqs have been acked.
		 */
		if (irq->config == VGIC_CONFIG_LEVEL && !(val & GICH_LR_STATE))
			irq->pending_latch = false;

		/*
		 * Level-triggered mapped IRQs are special because we only
		 * observe rising edges as input to the VGIC.
		 *
		 * If the guest never acked the interrupt we have to sample
		 * the physical line and set the line level, because the
		 * device state could have changed or we simply need to
		 * process the still pending interrupt later.
		 *
		 * If this causes us to lower the level, we have to also clear
		 * the physical active state, since we will otherwise never be
		 * told when the interrupt becomes asserted again.
		 */
		if (vgic_irq_is_mapped_level(irq) && (val & GICH_LR_PENDING_BIT)) {
			irq->line_level = vgic_get_phys_line_level(irq);

			if (!irq->line_level)
				vgic_irq_set_phys_active(irq, false);
		}

		raw_spin_unlock(&irq->irq_lock);
		vgic_put_irq(vcpu->kvm, irq);
	}

	vgic_cpu->used_lrs = 0;
}