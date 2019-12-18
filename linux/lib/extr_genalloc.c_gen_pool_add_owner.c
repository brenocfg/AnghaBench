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
struct gen_pool_chunk {unsigned long start_addr; unsigned long end_addr; int /*<<< orphan*/  next_chunk; int /*<<< orphan*/  avail; void* owner; int /*<<< orphan*/  phys_addr; } ;
struct gen_pool {size_t min_alloc_order; int /*<<< orphan*/  lock; int /*<<< orphan*/  chunks; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct gen_pool_chunk* vzalloc_node (int,int) ; 

int gen_pool_add_owner(struct gen_pool *pool, unsigned long virt, phys_addr_t phys,
		 size_t size, int nid, void *owner)
{
	struct gen_pool_chunk *chunk;
	int nbits = size >> pool->min_alloc_order;
	int nbytes = sizeof(struct gen_pool_chunk) +
				BITS_TO_LONGS(nbits) * sizeof(long);

	chunk = vzalloc_node(nbytes, nid);
	if (unlikely(chunk == NULL))
		return -ENOMEM;

	chunk->phys_addr = phys;
	chunk->start_addr = virt;
	chunk->end_addr = virt + size - 1;
	chunk->owner = owner;
	atomic_long_set(&chunk->avail, size);

	spin_lock(&pool->lock);
	list_add_rcu(&chunk->next_chunk, &pool->chunks);
	spin_unlock(&pool->lock);

	return 0;
}