#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vgic_irq {int intid; int active_source; int hwintid; scalar_t__ config; int pending_latch; int source; int line_level; int priority; scalar_t__ active; scalar_t__ hw; scalar_t__ group; } ;
struct TYPE_4__ {int* vgic_lr; } ;
struct TYPE_5__ {TYPE_1__ vgic_v2; } ;
struct TYPE_6__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int GICH_LR_ACTIVE_BIT ; 
 int GICH_LR_EOI ; 
 int GICH_LR_GROUP1 ; 
 int GICH_LR_HW ; 
 int GICH_LR_PENDING_BIT ; 
 int GICH_LR_PHYSID_CPUID_SHIFT ; 
 int GICH_LR_PRIORITY_SHIFT ; 
 scalar_t__ VGIC_CONFIG_EDGE ; 
 scalar_t__ VGIC_CONFIG_LEVEL ; 
 scalar_t__ WARN_RATELIMIT (int,char*,int) ; 
 int ffs (int) ; 
 scalar_t__ irq_is_pending (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_mapped_level (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_multi_sgi (struct vgic_irq*) ; 
 scalar_t__ vgic_irq_is_sgi (int) ; 

void vgic_v2_populate_lr(struct kvm_vcpu *vcpu, struct vgic_irq *irq, int lr)
{
	u32 val = irq->intid;
	bool allow_pending = true;

	if (irq->active) {
		val |= GICH_LR_ACTIVE_BIT;
		if (vgic_irq_is_sgi(irq->intid))
			val |= irq->active_source << GICH_LR_PHYSID_CPUID_SHIFT;
		if (vgic_irq_is_multi_sgi(irq)) {
			allow_pending = false;
			val |= GICH_LR_EOI;
		}
	}

	if (irq->group)
		val |= GICH_LR_GROUP1;

	if (irq->hw) {
		val |= GICH_LR_HW;
		val |= irq->hwintid << GICH_LR_PHYSID_CPUID_SHIFT;
		/*
		 * Never set pending+active on a HW interrupt, as the
		 * pending state is kept at the physical distributor
		 * level.
		 */
		if (irq->active)
			allow_pending = false;
	} else {
		if (irq->config == VGIC_CONFIG_LEVEL) {
			val |= GICH_LR_EOI;

			/*
			 * Software resampling doesn't work very well
			 * if we allow P+A, so let's not do that.
			 */
			if (irq->active)
				allow_pending = false;
		}
	}

	if (allow_pending && irq_is_pending(irq)) {
		val |= GICH_LR_PENDING_BIT;

		if (irq->config == VGIC_CONFIG_EDGE)
			irq->pending_latch = false;

		if (vgic_irq_is_sgi(irq->intid)) {
			u32 src = ffs(irq->source);

			if (WARN_RATELIMIT(!src, "No SGI source for INTID %d\n",
					   irq->intid))
				return;

			val |= (src - 1) << GICH_LR_PHYSID_CPUID_SHIFT;
			irq->source &= ~(1 << (src - 1));
			if (irq->source) {
				irq->pending_latch = true;
				val |= GICH_LR_EOI;
			}
		}
	}

	/*
	 * Level-triggered mapped IRQs are special because we only observe
	 * rising edges as input to the VGIC.  We therefore lower the line
	 * level here, so that we can take new virtual IRQs.  See
	 * vgic_v2_fold_lr_state for more info.
	 */
	if (vgic_irq_is_mapped_level(irq) && (val & GICH_LR_PENDING_BIT))
		irq->line_level = false;

	/* The GICv2 LR only holds five bits of priority. */
	val |= (irq->priority >> 3) << GICH_LR_PRIORITY_SHIFT;

	vcpu->arch.vgic_cpu.vgic_v2.vgic_lr[lr] = val;
}