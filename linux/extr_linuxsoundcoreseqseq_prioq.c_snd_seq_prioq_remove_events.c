#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_remove_events {int dummy; } ;
struct snd_seq_prioq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cells; struct snd_seq_event_cell* tail; struct snd_seq_event_cell* head; } ;
struct TYPE_3__ {int client; } ;
struct TYPE_4__ {TYPE_1__ source; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; TYPE_2__ event; } ;

/* Variables and functions */
 scalar_t__ prioq_remove_match (struct snd_seq_remove_events*,TYPE_2__*) ; 
 int /*<<< orphan*/  snd_seq_cell_free (struct snd_seq_event_cell*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_prioq_remove_events(struct snd_seq_prioq * f, int client,
				 struct snd_seq_remove_events *info)
{
	struct snd_seq_event_cell *cell, *next;
	unsigned long flags;
	struct snd_seq_event_cell *prev = NULL;
	struct snd_seq_event_cell *freefirst = NULL, *freeprev = NULL, *freenext;

	/* collect all removed cells */
	spin_lock_irqsave(&f->lock, flags);
	cell = f->head;

	while (cell) {
		next = cell->next;
		if (cell->event.source.client == client &&
			prioq_remove_match(info, &cell->event)) {

			/* remove cell from prioq */
			if (cell == f->head) {
				f->head = cell->next;
			} else {
				prev->next = cell->next;
			}

			if (cell == f->tail)
				f->tail = cell->next;
			f->cells--;

			/* add cell to free list */
			cell->next = NULL;
			if (freefirst == NULL) {
				freefirst = cell;
			} else {
				freeprev->next = cell;
			}

			freeprev = cell;
		} else {
			prev = cell;
		}
		cell = next;		
	}
	spin_unlock_irqrestore(&f->lock, flags);	

	/* remove selected cells */
	while (freefirst) {
		freenext = freefirst->next;
		snd_seq_cell_free(freefirst);
		freefirst = freenext;
	}
}