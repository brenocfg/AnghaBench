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
struct dma_coherent_mem {void* virt_base; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  bitmap; } ;
struct device {struct dma_coherent_mem* dma_mem; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 void* ERR_PTR (int) ; 
 size_t PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PFN_DOWN (scalar_t__) ; 
 int bitmap_allocate_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_get_device_base (struct device*,struct dma_coherent_mem*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void *dma_mark_declared_memory_occupied(struct device *dev,
					dma_addr_t device_addr, size_t size)
{
	struct dma_coherent_mem *mem = dev->dma_mem;
	unsigned long flags;
	int pos, err;

	size += device_addr & ~PAGE_MASK;

	if (!mem)
		return ERR_PTR(-EINVAL);

	spin_lock_irqsave(&mem->spinlock, flags);
	pos = PFN_DOWN(device_addr - dma_get_device_base(dev, mem));
	err = bitmap_allocate_region(mem->bitmap, pos, get_order(size));
	spin_unlock_irqrestore(&mem->spinlock, flags);

	if (err != 0)
		return ERR_PTR(err);
	return mem->virt_base + (pos << PAGE_SHIFT);
}