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
struct snd_seq_queue {int /*<<< orphan*/  timer; int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; int /*<<< orphan*/  use_lock; int /*<<< orphan*/  timer_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_prioq_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_timer_close (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  snd_seq_timer_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_use_lock_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_delete(struct snd_seq_queue *q)
{
	/* stop and release the timer */
	mutex_lock(&q->timer_mutex);
	snd_seq_timer_stop(q->timer);
	snd_seq_timer_close(q);
	mutex_unlock(&q->timer_mutex);
	/* wait until access free */
	snd_use_lock_sync(&q->use_lock);
	/* release resources... */
	snd_seq_prioq_delete(&q->tickq);
	snd_seq_prioq_delete(&q->timeq);
	snd_seq_timer_delete(&q->timer);

	kfree(q);
}