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
struct snd_seq_fifo {int /*<<< orphan*/  lock; int /*<<< orphan*/  input_sleep; } ;
struct snd_seq_event_cell {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct snd_seq_event_cell* fifo_cell_out (struct snd_seq_fifo*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_fifo_cell_out(struct snd_seq_fifo *f,
			  struct snd_seq_event_cell **cellp, int nonblock)
{
	struct snd_seq_event_cell *cell;
	unsigned long flags;
	wait_queue_entry_t wait;

	if (snd_BUG_ON(!f))
		return -EINVAL;

	*cellp = NULL;
	init_waitqueue_entry(&wait, current);
	spin_lock_irqsave(&f->lock, flags);
	while ((cell = fifo_cell_out(f)) == NULL) {
		if (nonblock) {
			/* non-blocking - return immediately */
			spin_unlock_irqrestore(&f->lock, flags);
			return -EAGAIN;
		}
		set_current_state(TASK_INTERRUPTIBLE);
		add_wait_queue(&f->input_sleep, &wait);
		spin_unlock_irqrestore(&f->lock, flags);
		schedule();
		spin_lock_irqsave(&f->lock, flags);
		remove_wait_queue(&f->input_sleep, &wait);
		if (signal_pending(current)) {
			spin_unlock_irqrestore(&f->lock, flags);
			return -ERESTARTSYS;
		}
	}
	spin_unlock_irqrestore(&f->lock, flags);
	*cellp = cell;

	return 0;
}