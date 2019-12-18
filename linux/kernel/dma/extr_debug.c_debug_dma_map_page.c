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
struct dma_debug_entry {size_t offset; size_t size; int direction; int /*<<< orphan*/  map_err_type; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  pfn; int /*<<< orphan*/  type; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_ERR_NOT_CHECKED ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  add_dma_entry (struct dma_debug_entry*) ; 
 int /*<<< orphan*/  check_for_illegal_area (struct device*,void*,size_t) ; 
 int /*<<< orphan*/  check_for_stack (struct device*,struct page*,size_t) ; 
 int /*<<< orphan*/  dma_debug_disabled () ; 
 int /*<<< orphan*/  dma_debug_single ; 
 struct dma_debug_entry* dma_entry_alloc () ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void debug_dma_map_page(struct device *dev, struct page *page, size_t offset,
			size_t size, int direction, dma_addr_t dma_addr)
{
	struct dma_debug_entry *entry;

	if (unlikely(dma_debug_disabled()))
		return;

	if (dma_mapping_error(dev, dma_addr))
		return;

	entry = dma_entry_alloc();
	if (!entry)
		return;

	entry->dev       = dev;
	entry->type      = dma_debug_single;
	entry->pfn	 = page_to_pfn(page);
	entry->offset	 = offset,
	entry->dev_addr  = dma_addr;
	entry->size      = size;
	entry->direction = direction;
	entry->map_err_type = MAP_ERR_NOT_CHECKED;

	check_for_stack(dev, page, offset);

	if (!PageHighMem(page)) {
		void *addr = page_address(page) + offset;

		check_for_illegal_area(dev, addr, size);
	}

	add_dma_entry(entry);
}