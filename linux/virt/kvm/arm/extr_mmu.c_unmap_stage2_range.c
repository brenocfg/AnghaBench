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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ stage2_pgd_addr_end (struct kvm*,scalar_t__,scalar_t__) ; 
 int stage2_pgd_index (struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  stage2_pgd_none (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_stage2_puds (struct kvm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void unmap_stage2_range(struct kvm *kvm, phys_addr_t start, u64 size)
{
	pgd_t *pgd;
	phys_addr_t addr = start, end = start + size;
	phys_addr_t next;

	assert_spin_locked(&kvm->mmu_lock);
	WARN_ON(size & ~PAGE_MASK);

	pgd = kvm->arch.pgd + stage2_pgd_index(kvm, addr);
	do {
		/*
		 * Make sure the page table is still active, as another thread
		 * could have possibly freed the page table, while we released
		 * the lock.
		 */
		if (!READ_ONCE(kvm->arch.pgd))
			break;
		next = stage2_pgd_addr_end(kvm, addr, end);
		if (!stage2_pgd_none(kvm, *pgd))
			unmap_stage2_puds(kvm, pgd, addr, next);
		/*
		 * If the range is too large, release the kvm->mmu_lock
		 * to prevent starvation and lockup detector warnings.
		 */
		if (next != end)
			cond_resched_lock(&kvm->mmu_lock);
	} while (pgd++, addr = next, addr != end);
}