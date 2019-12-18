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
struct mmu_gather_batch {struct mmu_gather_batch* next; } ;
struct TYPE_2__ {struct mmu_gather_batch* next; } ;
struct mmu_gather {TYPE_1__ local; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlb_batch_list_free(struct mmu_gather *tlb)
{
	struct mmu_gather_batch *batch, *next;

	for (batch = tlb->local.next; batch; batch = next) {
		next = batch->next;
		free_pages((unsigned long)batch, 0);
	}
	tlb->local.next = NULL;
}