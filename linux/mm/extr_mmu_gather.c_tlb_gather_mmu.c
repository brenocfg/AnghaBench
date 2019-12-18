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
struct TYPE_2__ {int /*<<< orphan*/  max; scalar_t__ nr; int /*<<< orphan*/ * next; } ;
struct mmu_gather {int fullmm; struct mm_struct* mm; scalar_t__ page_size; int /*<<< orphan*/ * batch; scalar_t__ batch_count; TYPE_1__ local; TYPE_1__* active; int /*<<< orphan*/  __pages; scalar_t__ need_flush_all; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tlb_reset_range (struct mmu_gather*) ; 
 int /*<<< orphan*/  inc_tlb_flush_pending (struct mm_struct*) ; 

void tlb_gather_mmu(struct mmu_gather *tlb, struct mm_struct *mm,
			unsigned long start, unsigned long end)
{
	tlb->mm = mm;

	/* Is it from 0 to ~0? */
	tlb->fullmm     = !(start | (end+1));

#ifndef CONFIG_HAVE_MMU_GATHER_NO_GATHER
	tlb->need_flush_all = 0;
	tlb->local.next = NULL;
	tlb->local.nr   = 0;
	tlb->local.max  = ARRAY_SIZE(tlb->__pages);
	tlb->active     = &tlb->local;
	tlb->batch_count = 0;
#endif

#ifdef CONFIG_HAVE_RCU_TABLE_FREE
	tlb->batch = NULL;
#endif
#ifdef CONFIG_HAVE_MMU_GATHER_PAGE_SIZE
	tlb->page_size = 0;
#endif

	__tlb_reset_range(tlb);
	inc_tlb_flush_pending(tlb->mm);
}