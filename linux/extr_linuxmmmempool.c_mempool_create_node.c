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
typedef  int /*<<< orphan*/  mempool_t ;
typedef  int /*<<< orphan*/  mempool_free_t ;
typedef  int /*<<< orphan*/  mempool_alloc_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mempool_init_node (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 

mempool_t *mempool_create_node(int min_nr, mempool_alloc_t *alloc_fn,
			       mempool_free_t *free_fn, void *pool_data,
			       gfp_t gfp_mask, int node_id)
{
	mempool_t *pool;

	pool = kzalloc_node(sizeof(*pool), gfp_mask, node_id);
	if (!pool)
		return NULL;

	if (mempool_init_node(pool, min_nr, alloc_fn, free_fn, pool_data,
			      gfp_mask, node_id)) {
		kfree(pool);
		return NULL;
	}

	return pool;
}