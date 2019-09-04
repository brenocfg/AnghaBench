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
struct mmu_gather {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  dec_tlb_flush_pending (int /*<<< orphan*/ ) ; 
 int mm_tlb_flush_nested (int /*<<< orphan*/ ) ; 

void tlb_finish_mmu(struct mmu_gather *tlb,
		unsigned long start, unsigned long end)
{
	/*
	 * If there are parallel threads are doing PTE changes on same range
	 * under non-exclusive lock(e.g., mmap_sem read-side) but defer TLB
	 * flush by batching, a thread has stable TLB entry can fail to flush
	 * the TLB by observing pte_none|!pte_dirty, for example so flush TLB
	 * forcefully if we detect parallel PTE batching threads.
	 */
	bool force = mm_tlb_flush_nested(tlb->mm);

	arch_tlb_finish_mmu(tlb, start, end, force);
	dec_tlb_flush_pending(tlb->mm);
}