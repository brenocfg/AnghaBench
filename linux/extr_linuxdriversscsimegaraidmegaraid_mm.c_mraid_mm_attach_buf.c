#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pool_index; int free_buf; int /*<<< orphan*/ * buf_vaddr; int /*<<< orphan*/  buf_paddr; } ;
typedef  TYPE_1__ uioc_t ;
struct TYPE_7__ {TYPE_3__* dma_pool_list; } ;
typedef  TYPE_2__ mraid_mmadp_t ;
struct TYPE_8__ {int buf_size; int in_use; int /*<<< orphan*/  lock; int /*<<< orphan*/  handle; int /*<<< orphan*/  paddr; int /*<<< orphan*/ * vaddr; } ;
typedef  TYPE_3__ mm_dmapool_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_DMA_POOLS ; 
 int /*<<< orphan*/ * dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
mraid_mm_attach_buf(mraid_mmadp_t *adp, uioc_t *kioc, int xferlen)
{
	mm_dmapool_t	*pool;
	int		right_pool = -1;
	unsigned long	flags;
	int		i;

	kioc->pool_index	= -1;
	kioc->buf_vaddr		= NULL;
	kioc->buf_paddr		= 0;
	kioc->free_buf		= 0;

	/*
	 * We need xferlen amount of memory. See if we can get it from our
	 * dma pools. If we don't get exact size, we will try bigger buffer
	 */

	for (i = 0; i < MAX_DMA_POOLS; i++) {

		pool = &adp->dma_pool_list[i];

		if (xferlen > pool->buf_size)
			continue;

		if (right_pool == -1)
			right_pool = i;

		spin_lock_irqsave(&pool->lock, flags);

		if (!pool->in_use) {

			pool->in_use		= 1;
			kioc->pool_index	= i;
			kioc->buf_vaddr		= pool->vaddr;
			kioc->buf_paddr		= pool->paddr;

			spin_unlock_irqrestore(&pool->lock, flags);
			return 0;
		}
		else {
			spin_unlock_irqrestore(&pool->lock, flags);
			continue;
		}
	}

	/*
	 * If xferlen doesn't match any of our pools, return error
	 */
	if (right_pool == -1)
		return -EINVAL;

	/*
	 * We did not get any buffer from the preallocated pool. Let us try
	 * to allocate one new buffer. NOTE: This is a blocking call.
	 */
	pool = &adp->dma_pool_list[right_pool];

	spin_lock_irqsave(&pool->lock, flags);

	kioc->pool_index	= right_pool;
	kioc->free_buf		= 1;
	kioc->buf_vaddr		= dma_pool_alloc(pool->handle, GFP_ATOMIC,
							&kioc->buf_paddr);
	spin_unlock_irqrestore(&pool->lock, flags);

	if (!kioc->buf_vaddr)
		return -ENOMEM;

	return 0;
}