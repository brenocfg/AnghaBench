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
typedef  scalar_t__ u64 ;
struct rx_ring_info {int rbr_table_size; scalar_t__ rbr_index; int /*<<< orphan*/ * rbr; struct page** rxhash; } ;
struct page {int /*<<< orphan*/ * mapping; scalar_t__ index; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_page ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MAX_RBR_RING_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_rbr_free(struct niu *np, struct rx_ring_info *rp)
{
	int i;

	for (i = 0; i < MAX_RBR_RING_SIZE; i++) {
		struct page *page;

		page = rp->rxhash[i];
		while (page) {
			struct page *next = (struct page *) page->mapping;
			u64 base = page->index;

			np->ops->unmap_page(np->device, base, PAGE_SIZE,
					    DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = NULL;

			__free_page(page);

			page = next;
		}
	}

	for (i = 0; i < rp->rbr_table_size; i++)
		rp->rbr[i] = cpu_to_le32(0);
	rp->rbr_index = 0;
}