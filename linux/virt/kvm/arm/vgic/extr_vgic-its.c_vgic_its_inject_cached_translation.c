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
typedef  int u64 ;
struct vgic_irq {int pending_latch; int /*<<< orphan*/  irq_lock; } ;
struct kvm_msi {int address_lo; int /*<<< orphan*/  data; int /*<<< orphan*/  devid; scalar_t__ address_hi; } ;
struct kvm {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_its_check_cache (struct kvm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_queue_irq_unlock (struct kvm*,struct vgic_irq*,unsigned long) ; 

int vgic_its_inject_cached_translation(struct kvm *kvm, struct kvm_msi *msi)
{
	struct vgic_irq *irq;
	unsigned long flags;
	phys_addr_t db;

	db = (u64)msi->address_hi << 32 | msi->address_lo;
	irq = vgic_its_check_cache(kvm, db, msi->devid, msi->data);

	if (!irq)
		return -1;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->pending_latch = true;
	vgic_queue_irq_unlock(kvm, irq, flags);

	return 0;
}