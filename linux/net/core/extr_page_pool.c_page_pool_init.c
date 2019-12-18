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
struct page_pool_params {int dummy; } ;
struct TYPE_2__ {int flags; int pool_size; scalar_t__ dma_dir; int /*<<< orphan*/  dev; } ;
struct page_pool {TYPE_1__ p; int /*<<< orphan*/  user_cnt; int /*<<< orphan*/  pages_state_release_cnt; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 scalar_t__ DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PP_FLAG_ALL ; 
 int PP_FLAG_DMA_MAP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct page_pool_params const*,int) ; 
 scalar_t__ ptr_ring_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int page_pool_init(struct page_pool *pool,
			  const struct page_pool_params *params)
{
	unsigned int ring_qsize = 1024; /* Default */

	memcpy(&pool->p, params, sizeof(pool->p));

	/* Validate only known flags were used */
	if (pool->p.flags & ~(PP_FLAG_ALL))
		return -EINVAL;

	if (pool->p.pool_size)
		ring_qsize = pool->p.pool_size;

	/* Sanity limit mem that can be pinned down */
	if (ring_qsize > 32768)
		return -E2BIG;

	/* DMA direction is either DMA_FROM_DEVICE or DMA_BIDIRECTIONAL.
	 * DMA_BIDIRECTIONAL is for allowing page used for DMA sending,
	 * which is the XDP_TX use-case.
	 */
	if ((pool->p.dma_dir != DMA_FROM_DEVICE) &&
	    (pool->p.dma_dir != DMA_BIDIRECTIONAL))
		return -EINVAL;

	if (ptr_ring_init(&pool->ring, ring_qsize, GFP_KERNEL) < 0)
		return -ENOMEM;

	atomic_set(&pool->pages_state_release_cnt, 0);

	/* Driver calling page_pool_create() also call page_pool_destroy() */
	refcount_set(&pool->user_cnt, 1);

	if (pool->p.flags & PP_FLAG_DMA_MAP)
		get_device(pool->p.dev);

	return 0;
}