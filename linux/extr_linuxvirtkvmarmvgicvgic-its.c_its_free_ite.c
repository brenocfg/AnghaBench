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
struct kvm {int dummy; } ;
struct its_ite {TYPE_1__* irq; int /*<<< orphan*/  ite_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_irq; scalar_t__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_unmap_vlpi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct its_ite*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_put_irq (struct kvm*,TYPE_1__*) ; 

__attribute__((used)) static void its_free_ite(struct kvm *kvm, struct its_ite *ite)
{
	list_del(&ite->ite_list);

	/* This put matches the get in vgic_add_lpi. */
	if (ite->irq) {
		if (ite->irq->hw)
			WARN_ON(its_unmap_vlpi(ite->irq->host_irq));

		vgic_put_irq(kvm, ite->irq);
	}

	kfree(ite);
}