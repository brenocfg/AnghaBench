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
struct mmu_gather_batch {struct mmu_gather_batch* next; int /*<<< orphan*/  max; scalar_t__ nr; } ;
struct mmu_gather {scalar_t__ batch_count; struct mmu_gather_batch* active; } ;

/* Variables and functions */
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  MAX_GATHER_BATCH ; 
 scalar_t__ MAX_GATHER_BATCH_COUNT ; 
 int __GFP_NOWARN ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tlb_next_batch(struct mmu_gather *tlb)
{
	struct mmu_gather_batch *batch;

	batch = tlb->active;
	if (batch->next) {
		tlb->active = batch->next;
		return true;
	}

	if (tlb->batch_count == MAX_GATHER_BATCH_COUNT)
		return false;

	batch = (void *)__get_free_pages(GFP_NOWAIT | __GFP_NOWARN, 0);
	if (!batch)
		return false;

	tlb->batch_count++;
	batch->next = NULL;
	batch->nr   = 0;
	batch->max  = MAX_GATHER_BATCH;

	tlb->active->next = batch;
	tlb->active = batch;

	return true;
}