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
 int /*<<< orphan*/  check_unmap (struct dma_debug_entry*) ; 
 int /*<<< orphan*/  dma_debug_coherent ; 
 int /*<<< orphan*/  dma_debug_disabled () ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 
 int /*<<< orphan*/  vmalloc_to_pfn (void*) ; 

void debug_dma_free_coherent(struct device *dev, size_t size,
			 void *virt, dma_addr_t addr)
{
	struct dma_debug_entry ref = {
		.type           = dma_debug_coherent,
		.dev            = dev,
		.offset		= offset_in_page(virt),
		.dev_addr       = addr,
		.size           = size,
		.direction      = DMA_BIDIRECTIONAL,
	};

	/* handle vmalloc and linear addresses */
	if (!is_vmalloc_addr(virt) && !virt_addr_valid(virt))
		return;

	if (is_vmalloc_addr(virt))
		ref.pfn = vmalloc_to_pfn(virt);
	else
		ref.pfn = page_to_pfn(virt_to_page(virt));

	if (unlikely(dma_debug_disabled()))
		return;

	check_unmap(&ref);
}