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
struct dma_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; scalar_t__ dev; } ;
struct dma_page {void* vaddr; int offset; int /*<<< orphan*/  in_use; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (scalar_t__,char*,int /*<<< orphan*/ ,void*,unsigned long) ; 
 struct dma_page* pool_find_page (struct dma_pool*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,void*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)
{
	struct dma_page *page;
	unsigned long flags;
	unsigned int offset;

	spin_lock_irqsave(&pool->lock, flags);
	page = pool_find_page(pool, dma);
	if (!page) {
		spin_unlock_irqrestore(&pool->lock, flags);
		if (pool->dev)
			dev_err(pool->dev,
				"dma_pool_free %s, %p/%lx (bad dma)\n",
				pool->name, vaddr, (unsigned long)dma);
		else
			pr_err("dma_pool_free %s, %p/%lx (bad dma)\n",
			       pool->name, vaddr, (unsigned long)dma);
		return;
	}

	offset = vaddr - page->vaddr;
#ifdef	DMAPOOL_DEBUG
	if ((dma - page->dma) != offset) {
		spin_unlock_irqrestore(&pool->lock, flags);
		if (pool->dev)
			dev_err(pool->dev,
				"dma_pool_free %s, %p (bad vaddr)/%pad\n",
				pool->name, vaddr, &dma);
		else
			pr_err("dma_pool_free %s, %p (bad vaddr)/%pad\n",
			       pool->name, vaddr, &dma);
		return;
	}
	{
		unsigned int chain = page->offset;
		while (chain < pool->allocation) {
			if (chain != offset) {
				chain = *(int *)(page->vaddr + chain);
				continue;
			}
			spin_unlock_irqrestore(&pool->lock, flags);
			if (pool->dev)
				dev_err(pool->dev, "dma_pool_free %s, dma %pad already free\n",
					pool->name, &dma);
			else
				pr_err("dma_pool_free %s, dma %pad already free\n",
				       pool->name, &dma);
			return;
		}
	}
	memset(vaddr, POOL_POISON_FREED, pool->size);
#endif

	page->in_use--;
	*(int *)vaddr = page->offset;
	page->offset = offset;
	/*
	 * Resist a temptation to do
	 *    if (!is_page_busy(page)) pool_free_page(pool, page);
	 * Better have a few empty pages hang around.
	 */
	spin_unlock_irqrestore(&pool->lock, flags);
}