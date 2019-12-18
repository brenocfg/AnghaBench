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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct snd_seq_pool {int max_used; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_alloc_failures; int /*<<< orphan*/  event_alloc_success; int /*<<< orphan*/  counter; struct snd_seq_event_cell* free; scalar_t__ closing; int /*<<< orphan*/  output_sleep; int /*<<< orphan*/ * ptr; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;
struct mutex {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_seq_cell_alloc(struct snd_seq_pool *pool,
			      struct snd_seq_event_cell **cellp,
			      int nonblock, struct file *file,
			      struct mutex *mutexp)
{
	struct snd_seq_event_cell *cell;
	unsigned long flags;
	int err = -EAGAIN;
	wait_queue_entry_t wait;

	if (pool == NULL)
		return -EINVAL;

	*cellp = NULL;

	init_waitqueue_entry(&wait, current);
	spin_lock_irqsave(&pool->lock, flags);
	if (pool->ptr == NULL) {	/* not initialized */
		pr_debug("ALSA: seq: pool is not initialized\n");
		err = -EINVAL;
		goto __error;
	}
	while (pool->free == NULL && ! nonblock && ! pool->closing) {

		set_current_state(TASK_INTERRUPTIBLE);
		add_wait_queue(&pool->output_sleep, &wait);
		spin_unlock_irqrestore(&pool->lock, flags);
		if (mutexp)
			mutex_unlock(mutexp);
		schedule();
		if (mutexp)
			mutex_lock(mutexp);
		spin_lock_irqsave(&pool->lock, flags);
		remove_wait_queue(&pool->output_sleep, &wait);
		/* interrupted? */
		if (signal_pending(current)) {
			err = -ERESTARTSYS;
			goto __error;
		}
	}
	if (pool->closing) { /* closing.. */
		err = -ENOMEM;
		goto __error;
	}

	cell = pool->free;
	if (cell) {
		int used;
		pool->free = cell->next;
		atomic_inc(&pool->counter);
		used = atomic_read(&pool->counter);
		if (pool->max_used < used)
			pool->max_used = used;
		pool->event_alloc_success++;
		/* clear cell pointers */
		cell->next = NULL;
		err = 0;
	} else
		pool->event_alloc_failures++;
	*cellp = cell;

__error:
	spin_unlock_irqrestore(&pool->lock, flags);
	return err;
}