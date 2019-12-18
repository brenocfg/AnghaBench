#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_queue {int owner; int klocked; TYPE_1__* timer; int /*<<< orphan*/  owner_lock; } ;
struct TYPE_3__ {scalar_t__ running; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_timer_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_seq_timer_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_queue_client_termination(int client)
{
	unsigned long flags;
	int i;
	struct snd_seq_queue *q;

	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queueptr(i)) == NULL)
			continue;
		spin_lock_irqsave(&q->owner_lock, flags);
		if (q->owner == client)
			q->klocked = 1;
		spin_unlock_irqrestore(&q->owner_lock, flags);
		if (q->owner == client) {
			if (q->timer->running)
				snd_seq_timer_stop(q->timer);
			snd_seq_timer_reset(q->timer);
		}
		queuefree(q);
	}
}