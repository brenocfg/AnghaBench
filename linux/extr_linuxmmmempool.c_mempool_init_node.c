#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min_nr; int curr_nr; void* pool_data; void* (* alloc ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  elements; int /*<<< orphan*/  wait; int /*<<< orphan*/ * free; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mempool_t ;
typedef  int /*<<< orphan*/  mempool_free_t ;
typedef  void* (* mempool_alloc_t ) (int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  add_element (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc_array_node (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ unlikely (int) ; 

int mempool_init_node(mempool_t *pool, int min_nr, mempool_alloc_t *alloc_fn,
		      mempool_free_t *free_fn, void *pool_data,
		      gfp_t gfp_mask, int node_id)
{
	spin_lock_init(&pool->lock);
	pool->min_nr	= min_nr;
	pool->pool_data = pool_data;
	pool->alloc	= alloc_fn;
	pool->free	= free_fn;
	init_waitqueue_head(&pool->wait);

	pool->elements = kmalloc_array_node(min_nr, sizeof(void *),
					    gfp_mask, node_id);
	if (!pool->elements)
		return -ENOMEM;

	/*
	 * First pre-allocate the guaranteed number of buffers.
	 */
	while (pool->curr_nr < pool->min_nr) {
		void *element;

		element = pool->alloc(gfp_mask, pool->pool_data);
		if (unlikely(!element)) {
			mempool_exit(pool);
			return -ENOMEM;
		}
		add_element(pool, element);
	}

	return 0;
}