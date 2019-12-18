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
struct mmu_gather_batch {scalar_t__ nr; int /*<<< orphan*/  pages; struct mmu_gather_batch* next; } ;
struct mmu_gather {struct mmu_gather_batch local; struct mmu_gather_batch* active; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_and_swap_cache (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tlb_batch_pages_flush(struct mmu_gather *tlb)
{
	struct mmu_gather_batch *batch;

	for (batch = &tlb->local; batch && batch->nr; batch = batch->next) {
		free_pages_and_swap_cache(batch->pages, batch->nr);
		batch->nr = 0;
	}
	tlb->active = &tlb->local;
}