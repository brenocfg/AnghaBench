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
struct snd_seq_fifo {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int snd_seq_unused_cells (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_fifo_unused_cells(struct snd_seq_fifo *f)
{
	unsigned long flags;
	int cells;

	if (!f)
		return 0;

	snd_use_lock_use(&f->use_lock);
	spin_lock_irqsave(&f->lock, flags);
	cells = snd_seq_unused_cells(f->pool);
	spin_unlock_irqrestore(&f->lock, flags);
	snd_use_lock_free(&f->use_lock);
	return cells;
}