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
struct snd_seq_prioq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cells; struct snd_seq_event_cell* tail; struct snd_seq_event_cell* head; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_is_ready (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct snd_seq_event_cell *snd_seq_prioq_cell_out(struct snd_seq_prioq *f,
						  void *current_time)
{
	struct snd_seq_event_cell *cell;
	unsigned long flags;

	if (f == NULL) {
		pr_debug("ALSA: seq: snd_seq_prioq_cell_in() called with NULL prioq\n");
		return NULL;
	}
	spin_lock_irqsave(&f->lock, flags);

	cell = f->head;
	if (cell && current_time && !event_is_ready(&cell->event, current_time))
		cell = NULL;
	if (cell) {
		f->head = cell->next;

		/* reset tail if this was the last element */
		if (f->tail == cell)
			f->tail = NULL;

		cell->next = NULL;
		f->cells--;
	}

	spin_unlock_irqrestore(&f->lock, flags);
	return cell;
}