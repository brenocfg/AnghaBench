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
struct snd_seq_pool {int /*<<< orphan*/  lock; scalar_t__ closing; scalar_t__ total_elements; int /*<<< orphan*/ * free; struct snd_seq_event_cell* ptr; int /*<<< orphan*/  counter; int /*<<< orphan*/  output_sleep; } ;
struct snd_seq_event_cell {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct snd_seq_event_cell*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_seq_pool_done(struct snd_seq_pool *pool)
{
	struct snd_seq_event_cell *ptr;

	if (snd_BUG_ON(!pool))
		return -EINVAL;

	/* wait for closing all threads */
	if (waitqueue_active(&pool->output_sleep))
		wake_up(&pool->output_sleep);

	while (atomic_read(&pool->counter) > 0)
		schedule_timeout_uninterruptible(1);
	
	/* release all resources */
	spin_lock_irq(&pool->lock);
	ptr = pool->ptr;
	pool->ptr = NULL;
	pool->free = NULL;
	pool->total_elements = 0;
	spin_unlock_irq(&pool->lock);

	kvfree(ptr);

	spin_lock_irq(&pool->lock);
	pool->closing = 0;
	spin_unlock_irq(&pool->lock);

	return 0;
}