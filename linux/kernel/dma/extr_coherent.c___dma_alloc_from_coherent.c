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
struct dma_coherent_mem {int size; int /*<<< orphan*/  spinlock; void* virt_base; scalar_t__ device_base; int /*<<< orphan*/  bitmap; } ;
typedef  int ssize_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *__dma_alloc_from_coherent(struct dma_coherent_mem *mem,
		ssize_t size, dma_addr_t *dma_handle)
{
	int order = get_order(size);
	unsigned long flags;
	int pageno;
	void *ret;

	spin_lock_irqsave(&mem->spinlock, flags);

	if (unlikely(size > (mem->size << PAGE_SHIFT)))
		goto err;

	pageno = bitmap_find_free_region(mem->bitmap, mem->size, order);
	if (unlikely(pageno < 0))
		goto err;

	/*
	 * Memory was found in the coherent area.
	 */
	*dma_handle = mem->device_base + (pageno << PAGE_SHIFT);
	ret = mem->virt_base + (pageno << PAGE_SHIFT);
	spin_unlock_irqrestore(&mem->spinlock, flags);
	memset(ret, 0, size);
	return ret;
err:
	spin_unlock_irqrestore(&mem->spinlock, flags);
	return NULL;
}