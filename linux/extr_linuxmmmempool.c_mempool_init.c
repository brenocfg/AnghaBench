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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int mempool_init_node (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mempool_init(mempool_t *pool, int min_nr, mempool_alloc_t *alloc_fn,
		 mempool_free_t *free_fn, void *pool_data)
{
	return mempool_init_node(pool, min_nr, alloc_fn, free_fn,
				 pool_data, GFP_KERNEL, NUMA_NO_NODE);

}