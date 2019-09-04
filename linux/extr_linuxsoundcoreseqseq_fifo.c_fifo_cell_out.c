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
struct snd_seq_fifo {int /*<<< orphan*/  cells; struct snd_seq_event_cell* tail; struct snd_seq_event_cell* head; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;

/* Variables and functions */

__attribute__((used)) static struct snd_seq_event_cell *fifo_cell_out(struct snd_seq_fifo *f)
{
	struct snd_seq_event_cell *cell;

	if ((cell = f->head) != NULL) {
		f->head = cell->next;

		/* reset tail if this was the last element */
		if (f->tail == cell)
			f->tail = NULL;

		cell->next = NULL;
		f->cells--;
	}

	return cell;
}