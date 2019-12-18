#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_queue {int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; TYPE_3__* timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  time; int /*<<< orphan*/  tick; } ;
struct TYPE_8__ {int queue; int flags; TYPE_2__ time; } ;
struct snd_seq_event_cell {TYPE_4__ event; } ;
struct TYPE_5__ {int /*<<< orphan*/  cur_tick; } ;
struct TYPE_7__ {int /*<<< orphan*/  cur_time; TYPE_1__ tick; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_SEQ_TIME_MODE_ABS ; 
 int SNDRV_SEQ_TIME_MODE_MASK ; 
 int SNDRV_SEQ_TIME_MODE_REL ; 
 int SNDRV_SEQ_TIME_STAMP_MASK ; 
#define  SNDRV_SEQ_TIME_STAMP_REAL 129 
#define  SNDRV_SEQ_TIME_STAMP_TICK 128 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_check_queue (struct snd_seq_queue*,int,int) ; 
 int /*<<< orphan*/  snd_seq_inc_real_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_seq_prioq_cell_in (int /*<<< orphan*/ ,struct snd_seq_event_cell*) ; 

int snd_seq_enqueue_event(struct snd_seq_event_cell *cell, int atomic, int hop)
{
	int dest, err;
	struct snd_seq_queue *q;

	if (snd_BUG_ON(!cell))
		return -EINVAL;
	dest = cell->event.queue;	/* destination queue */
	q = queueptr(dest);
	if (q == NULL)
		return -EINVAL;
	/* handle relative time stamps, convert them into absolute */
	if ((cell->event.flags & SNDRV_SEQ_TIME_MODE_MASK) == SNDRV_SEQ_TIME_MODE_REL) {
		switch (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) {
		case SNDRV_SEQ_TIME_STAMP_TICK:
			cell->event.time.tick += q->timer->tick.cur_tick;
			break;

		case SNDRV_SEQ_TIME_STAMP_REAL:
			snd_seq_inc_real_time(&cell->event.time.time,
					      &q->timer->cur_time);
			break;
		}
		cell->event.flags &= ~SNDRV_SEQ_TIME_MODE_MASK;
		cell->event.flags |= SNDRV_SEQ_TIME_MODE_ABS;
	}
	/* enqueue event in the real-time or midi queue */
	switch (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) {
	case SNDRV_SEQ_TIME_STAMP_TICK:
		err = snd_seq_prioq_cell_in(q->tickq, cell);
		break;

	case SNDRV_SEQ_TIME_STAMP_REAL:
	default:
		err = snd_seq_prioq_cell_in(q->timeq, cell);
		break;
	}

	if (err < 0) {
		queuefree(q); /* unlock */
		return err;
	}

	/* trigger dispatching */
	snd_seq_check_queue(q, atomic, hop);

	queuefree(q); /* unlock */

	return 0;
}