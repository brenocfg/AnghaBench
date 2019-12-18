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
struct TYPE_2__ {scalar_t__ pgd_phys; int /*<<< orphan*/ * pgd; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 void* READ_ONCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages_exact (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_phys_size (struct kvm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage2_pgd_size (struct kvm*) ; 
 int /*<<< orphan*/  unmap_stage2_range (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_free_stage2_pgd(struct kvm *kvm)
{
	void *pgd = NULL;

	spin_lock(&kvm->mmu_lock);
	if (kvm->arch.pgd) {
		unmap_stage2_range(kvm, 0, kvm_phys_size(kvm));
		pgd = READ_ONCE(kvm->arch.pgd);
		kvm->arch.pgd = NULL;
		kvm->arch.pgd_phys = 0;
	}
	spin_unlock(&kvm->mmu_lock);

	/* Free the HW pgd, one page at a time */
	if (pgd)
		free_pages_exact(pgd, stage2_pgd_size(kvm));
}