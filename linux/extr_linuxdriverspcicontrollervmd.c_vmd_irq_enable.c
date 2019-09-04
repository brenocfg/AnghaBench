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
struct vmd_irq {int enabled; TYPE_2__* irq; int /*<<< orphan*/  node; } ;
struct irq_data {TYPE_1__* chip; struct vmd_irq* chip_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_unmask ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void vmd_irq_enable(struct irq_data *data)
{
	struct vmd_irq *vmdirq = data->chip_data;
	unsigned long flags;

	raw_spin_lock_irqsave(&list_lock, flags);
	WARN_ON(vmdirq->enabled);
	list_add_tail_rcu(&vmdirq->node, &vmdirq->irq->irq_list);
	vmdirq->enabled = true;
	raw_spin_unlock_irqrestore(&list_lock, flags);

	data->chip->irq_unmask(data);
}