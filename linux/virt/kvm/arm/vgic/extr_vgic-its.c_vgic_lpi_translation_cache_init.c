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
struct vgic_translation_cache_entry {int /*<<< orphan*/  entry; } ;
struct vgic_dist {int /*<<< orphan*/  lpi_translation_cache; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {int /*<<< orphan*/  online_vcpus; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int LPI_DEFAULT_PCPU_CACHE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 struct vgic_translation_cache_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void vgic_lpi_translation_cache_init(struct kvm *kvm)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	unsigned int sz;
	int i;

	if (!list_empty(&dist->lpi_translation_cache))
		return;

	sz = atomic_read(&kvm->online_vcpus) * LPI_DEFAULT_PCPU_CACHE_SIZE;

	for (i = 0; i < sz; i++) {
		struct vgic_translation_cache_entry *cte;

		/* An allocation failure is not fatal */
		cte = kzalloc(sizeof(*cte), GFP_KERNEL);
		if (WARN_ON(!cte))
			break;

		INIT_LIST_HEAD(&cte->entry);
		list_add(&cte->entry, &dist->lpi_translation_cache);
	}
}