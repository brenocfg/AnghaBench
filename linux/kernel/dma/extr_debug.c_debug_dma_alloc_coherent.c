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
struct dma_debug_entry {size_t size; int /*<<< orphan*/  pfn; int /*<<< orphan*/  direction; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  offset; struct device* dev; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  add_dma_entry (struct dma_debug_entry*) ; 
 int /*<<< orphan*/  dma_debug_coherent ; 
 int /*<<< orphan*/  dma_debug_disabled () ; 
 struct dma_debug_entry* dma_entry_alloc () ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 
 int /*<<< orphan*/  vmalloc_to_pfn (void*) ; 

void debug_dma_alloc_coherent(struct device *dev, size_t size,
			      dma_addr_t dma_addr, void *virt)
{
	struct dma_debug_entry *entry;

	if (unlikely(dma_debug_disabled()))
		return;

	if (unlikely(virt == NULL))
		return;

	/* handle vmalloc and linear addresses */
	if (!is_vmalloc_addr(virt) && !virt_addr_valid(virt))
		return;

	entry = dma_entry_alloc();
	if (!entry)
		return;

	entry->type      = dma_debug_coherent;
	entry->dev       = dev;
	entry->offset	 = offset_in_page(virt);
	entry->size      = size;
	entry->dev_addr  = dma_addr;
	entry->direction = DMA_BIDIRECTIONAL;

	if (is_vmalloc_addr(virt))
		entry->pfn = vmalloc_to_pfn(virt);
	else
		entry->pfn = page_to_pfn(virt_to_page(virt));

	add_dma_entry(entry);
}