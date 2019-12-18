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
struct page {int dummy; } ;
struct mmu_gather_batch {scalar_t__ nr; scalar_t__ max; struct page** pages; } ;
struct mmu_gather {int page_size; struct mmu_gather_batch* active; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int /*<<< orphan*/  tlb_next_batch (struct mmu_gather*) ; 

bool __tlb_remove_page_size(struct mmu_gather *tlb, struct page *page, int page_size)
{
	struct mmu_gather_batch *batch;

	VM_BUG_ON(!tlb->end);

#ifdef CONFIG_HAVE_MMU_GATHER_PAGE_SIZE
	VM_WARN_ON(tlb->page_size != page_size);
#endif

	batch = tlb->active;
	/*
	 * Add the page and check if we are full. If so
	 * force a flush.
	 */
	batch->pages[batch->nr++] = page;
	if (batch->nr == batch->max) {
		if (!tlb_next_batch(tlb))
			return true;
		batch = tlb->active;
	}
	VM_BUG_ON_PAGE(batch->nr > batch->max, page);

	return false;
}