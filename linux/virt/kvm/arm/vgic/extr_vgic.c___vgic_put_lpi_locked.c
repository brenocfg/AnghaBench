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
struct vgic_irq {int /*<<< orphan*/  lpi_list; int /*<<< orphan*/  refcount; } ;
struct vgic_dist {int /*<<< orphan*/  lpi_list_count; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vgic_irq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_irq_release ; 

void __vgic_put_lpi_locked(struct kvm *kvm, struct vgic_irq *irq)
{
	struct vgic_dist *dist = &kvm->arch.vgic;

	if (!kref_put(&irq->refcount, vgic_irq_release))
		return;

	list_del(&irq->lpi_list);
	dist->lpi_list_count--;

	kfree(irq);
}