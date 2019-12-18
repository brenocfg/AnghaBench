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
struct snd_seq_pool {int size; int room; int total_elements; int /*<<< orphan*/  lock; scalar_t__ max_used; struct snd_seq_event_cell* free; struct snd_seq_event_cell* ptr; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; struct snd_seq_pool* pool; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kvfree (struct snd_seq_event_cell*) ; 
 struct snd_seq_event_cell* kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_seq_pool_init(struct snd_seq_pool *pool)
{
	int cell;
	struct snd_seq_event_cell *cellptr;

	if (snd_BUG_ON(!pool))
		return -EINVAL;

	cellptr = kvmalloc_array(sizeof(struct snd_seq_event_cell), pool->size,
				 GFP_KERNEL);
	if (!cellptr)
		return -ENOMEM;

	/* add new cells to the free cell list */
	spin_lock_irq(&pool->lock);
	if (pool->ptr) {
		spin_unlock_irq(&pool->lock);
		kvfree(cellptr);
		return 0;
	}

	pool->ptr = cellptr;
	pool->free = NULL;

	for (cell = 0; cell < pool->size; cell++) {
		cellptr = pool->ptr + cell;
		cellptr->pool = pool;
		cellptr->next = pool->free;
		pool->free = cellptr;
	}
	pool->room = (pool->size + 1) / 2;

	/* init statistics */
	pool->max_used = 0;
	pool->total_elements = pool->size;
	spin_unlock_irq(&pool->lock);
	return 0;
}