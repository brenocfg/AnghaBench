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
struct vgic_dist {int /*<<< orphan*/  lpi_list_lock; int /*<<< orphan*/  lpi_translation_cache; int /*<<< orphan*/  lpi_list_head; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void kvm_vgic_early_init(struct kvm *kvm)
{
	struct vgic_dist *dist = &kvm->arch.vgic;

	INIT_LIST_HEAD(&dist->lpi_list_head);
	INIT_LIST_HEAD(&dist->lpi_translation_cache);
	raw_spin_lock_init(&dist->lpi_list_lock);
}