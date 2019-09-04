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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_release_from_contiguous (struct device*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ force_dma_unencrypted () ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 unsigned int get_order (size_t) ; 
 int /*<<< orphan*/  set_memory_encrypted (unsigned long,int) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

void dma_direct_free(struct device *dev, size_t size, void *cpu_addr,
		dma_addr_t dma_addr, unsigned long attrs)
{
	unsigned int count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	unsigned int page_order = get_order(size);

	if (force_dma_unencrypted())
		set_memory_encrypted((unsigned long)cpu_addr, 1 << page_order);
	if (!dma_release_from_contiguous(dev, virt_to_page(cpu_addr), count))
		free_pages((unsigned long)cpu_addr, page_order);
}