#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  output_sleep; struct snd_seq_event_cell* free; } ;
struct TYPE_4__ {int len; struct snd_seq_event_cell* ptr; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
struct TYPE_6__ {TYPE_2__ data; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; TYPE_3__ event; struct snd_seq_pool* pool; } ;

/* Variables and functions */
 int SNDRV_SEQ_EXT_CHAINED ; 
 int /*<<< orphan*/  free_cell (struct snd_seq_pool*,struct snd_seq_event_cell*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_seq_ev_is_variable (TYPE_3__*) ; 
 scalar_t__ snd_seq_output_ok (struct snd_seq_pool*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_seq_cell_free(struct snd_seq_event_cell * cell)
{
	unsigned long flags;
	struct snd_seq_pool *pool;

	if (snd_BUG_ON(!cell))
		return;
	pool = cell->pool;
	if (snd_BUG_ON(!pool))
		return;

	spin_lock_irqsave(&pool->lock, flags);
	free_cell(pool, cell);
	if (snd_seq_ev_is_variable(&cell->event)) {
		if (cell->event.data.ext.len & SNDRV_SEQ_EXT_CHAINED) {
			struct snd_seq_event_cell *curp, *nextptr;
			curp = cell->event.data.ext.ptr;
			for (; curp; curp = nextptr) {
				nextptr = curp->next;
				curp->next = pool->free;
				free_cell(pool, curp);
			}
		}
	}
	if (waitqueue_active(&pool->output_sleep)) {
		/* has enough space now? */
		if (snd_seq_output_ok(pool))
			wake_up(&pool->output_sleep);
	}
	spin_unlock_irqrestore(&pool->lock, flags);
}