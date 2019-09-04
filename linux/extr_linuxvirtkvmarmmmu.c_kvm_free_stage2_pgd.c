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
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PHYS_SIZE ; 
 void* READ_ONCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S2_PGD_SIZE ; 
 int /*<<< orphan*/  free_pages_exact (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_stage2_range (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_free_stage2_pgd(struct kvm *kvm)
{
	void *pgd = NULL;

	spin_lock(&kvm->mmu_lock);
	if (kvm->arch.pgd) {
		unmap_stage2_range(kvm, 0, KVM_PHYS_SIZE);
		pgd = READ_ONCE(kvm->arch.pgd);
		kvm->arch.pgd = NULL;
	}
	spin_unlock(&kvm->mmu_lock);

	/* Free the HW pgd, one page at a time */
	if (pgd)
		free_pages_exact(pgd, S2_PGD_SIZE);
}