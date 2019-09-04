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
struct vmd_irq {TYPE_1__* irq; } ;
struct msi_domain_info {int dummy; } ;
struct irq_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 struct vmd_irq* irq_get_chip_data (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct vmd_irq*) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmd_msi_free(struct irq_domain *domain,
			struct msi_domain_info *info, unsigned int virq)
{
	struct vmd_irq *vmdirq = irq_get_chip_data(virq);
	unsigned long flags;

	synchronize_srcu(&vmdirq->irq->srcu);

	/* XXX: Potential optimization to rebalance */
	raw_spin_lock_irqsave(&list_lock, flags);
	vmdirq->irq->count--;
	raw_spin_unlock_irqrestore(&list_lock, flags);

	kfree(vmdirq);
}