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
struct vgic_irq {scalar_t__ intid; int /*<<< orphan*/  lpi_list; int /*<<< orphan*/  refcount; } ;
struct vgic_dist {int /*<<< orphan*/  lpi_list_lock; int /*<<< orphan*/  lpi_list_count; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ VGIC_MIN_LPI ; 
 int /*<<< orphan*/  kfree (struct vgic_irq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vgic_irq_release ; 

void vgic_put_irq(struct kvm *kvm, struct vgic_irq *irq)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	unsigned long flags;

	if (irq->intid < VGIC_MIN_LPI)
		return;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);
	if (!kref_put(&irq->refcount, vgic_irq_release)) {
		raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);
		return;
	};

	list_del(&irq->lpi_list);
	dist->lpi_list_count--;
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	kfree(irq);
}