#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_queue {int /*<<< orphan*/  timer; int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  time; int /*<<< orphan*/  tick; } ;
struct TYPE_10__ {TYPE_3__ skew; TYPE_2__ time; int /*<<< orphan*/  value; } ;
struct TYPE_11__ {TYPE_4__ param; } ;
struct TYPE_12__ {TYPE_5__ queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  client; } ;
struct snd_seq_event {int type; TYPE_6__ data; TYPE_1__ source; } ;

/* Variables and functions */
#define  SNDRV_SEQ_EVENT_CONTINUE 134 
#define  SNDRV_SEQ_EVENT_QUEUE_SKEW 133 
#define  SNDRV_SEQ_EVENT_SETPOS_TICK 132 
#define  SNDRV_SEQ_EVENT_SETPOS_TIME 131 
#define  SNDRV_SEQ_EVENT_START 130 
#define  SNDRV_SEQ_EVENT_STOP 129 
#define  SNDRV_SEQ_EVENT_TEMPO 128 
 int /*<<< orphan*/  queue_broadcast_event (struct snd_seq_queue*,struct snd_seq_event*,int,int) ; 
 int /*<<< orphan*/  snd_seq_prioq_leave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_timer_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_set_position_tick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_set_position_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_set_skew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_set_tempo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_seq_queue_process_event(struct snd_seq_queue *q,
					struct snd_seq_event *ev,
					int atomic, int hop)
{
	switch (ev->type) {
	case SNDRV_SEQ_EVENT_START:
		snd_seq_prioq_leave(q->tickq, ev->source.client, 1);
		snd_seq_prioq_leave(q->timeq, ev->source.client, 1);
		if (! snd_seq_timer_start(q->timer))
			queue_broadcast_event(q, ev, atomic, hop);
		break;

	case SNDRV_SEQ_EVENT_CONTINUE:
		if (! snd_seq_timer_continue(q->timer))
			queue_broadcast_event(q, ev, atomic, hop);
		break;

	case SNDRV_SEQ_EVENT_STOP:
		snd_seq_timer_stop(q->timer);
		queue_broadcast_event(q, ev, atomic, hop);
		break;

	case SNDRV_SEQ_EVENT_TEMPO:
		snd_seq_timer_set_tempo(q->timer, ev->data.queue.param.value);
		queue_broadcast_event(q, ev, atomic, hop);
		break;

	case SNDRV_SEQ_EVENT_SETPOS_TICK:
		if (snd_seq_timer_set_position_tick(q->timer, ev->data.queue.param.time.tick) == 0) {
			queue_broadcast_event(q, ev, atomic, hop);
		}
		break;

	case SNDRV_SEQ_EVENT_SETPOS_TIME:
		if (snd_seq_timer_set_position_time(q->timer, ev->data.queue.param.time.time) == 0) {
			queue_broadcast_event(q, ev, atomic, hop);
		}
		break;
	case SNDRV_SEQ_EVENT_QUEUE_SKEW:
		if (snd_seq_timer_set_skew(q->timer,
					   ev->data.queue.param.skew.value,
					   ev->data.queue.param.skew.base) == 0) {
			queue_broadcast_event(q, ev, atomic, hop);
		}
		break;
	}
}