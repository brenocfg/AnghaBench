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
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  mmu_lock; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ stage2_pgd_addr_end (struct kvm*,scalar_t__,scalar_t__) ; 
 int stage2_pgd_index (struct kvm*,scalar_t__) ; 
 scalar_t__ stage2_pgd_present (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_wp_puds (struct kvm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void stage2_wp_range(struct kvm *kvm, phys_addr_t addr, phys_addr_t end)
{
	pgd_t *pgd;
	phys_addr_t next;

	pgd = kvm->arch.pgd + stage2_pgd_index(kvm, addr);
	do {
		/*
		 * Release kvm_mmu_lock periodically if the memory region is
		 * large. Otherwise, we may see kernel panics with
		 * CONFIG_DETECT_HUNG_TASK, CONFIG_LOCKUP_DETECTOR,
		 * CONFIG_LOCKDEP. Additionally, holding the lock too long
		 * will also starve other vCPUs. We have to also make sure
		 * that the page tables are not freed while we released
		 * the lock.
		 */
		cond_resched_lock(&kvm->mmu_lock);
		if (!READ_ONCE(kvm->arch.pgd))
			break;
		next = stage2_pgd_addr_end(kvm, addr, end);
		if (stage2_pgd_present(kvm, *pgd))
			stage2_wp_puds(kvm, pgd, addr, next);
	} while (pgd++, addr = next, addr != end);
}