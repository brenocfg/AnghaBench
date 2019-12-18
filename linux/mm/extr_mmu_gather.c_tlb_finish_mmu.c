#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmu_gather {int fullmm; int freed_tables; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tlb_reset_range (struct mmu_gather*) ; 
 int /*<<< orphan*/  dec_tlb_flush_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ mm_tlb_flush_nested (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_batch_list_free (struct mmu_gather*) ; 
 int /*<<< orphan*/  tlb_flush_mmu (struct mmu_gather*) ; 

void tlb_finish_mmu(struct mmu_gather *tlb,
		unsigned long start, unsigned long end)
{
	/*
	 * If there are parallel threads are doing PTE changes on same range
	 * under non-exclusive lock (e.g., mmap_sem read-side) but defer TLB
	 * flush by batching, one thread may end up seeing inconsistent PTEs
	 * and result in having stale TLB entries.  So flush TLB forcefully
	 * if we detect parallel PTE batching threads.
	 *
	 * However, some syscalls, e.g. munmap(), may free page tables, this
	 * needs force flush everything in the given range. Otherwise this
	 * may result in having stale TLB entries for some architectures,
	 * e.g. aarch64, that could specify flush what level TLB.
	 */
	if (mm_tlb_flush_nested(tlb->mm)) {
		/*
		 * The aarch64 yields better performance with fullmm by
		 * avoiding multiple CPUs spamming TLBI messages at the
		 * same time.
		 *
		 * On x86 non-fullmm doesn't yield significant difference
		 * against fullmm.
		 */
		tlb->fullmm = 1;
		__tlb_reset_range(tlb);
		tlb->freed_tables = 1;
	}

	tlb_flush_mmu(tlb);

#ifndef CONFIG_HAVE_MMU_GATHER_NO_GATHER
	tlb_batch_list_free(tlb);
#endif
	dec_tlb_flush_pending(tlb->mm);
}