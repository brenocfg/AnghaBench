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
struct snd_seq_queue {int queue; int owner; int locked; scalar_t__ klocked; int /*<<< orphan*/ * timer; int /*<<< orphan*/ * timeq; int /*<<< orphan*/ * tickq; int /*<<< orphan*/  use_lock; int /*<<< orphan*/  timer_mutex; int /*<<< orphan*/  check_lock; int /*<<< orphan*/  owner_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_prioq_delete (int /*<<< orphan*/ **) ; 
 void* snd_seq_prioq_new () ; 
 int /*<<< orphan*/  snd_seq_timer_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * snd_seq_timer_new () ; 
 int /*<<< orphan*/  snd_use_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct snd_seq_queue *queue_new(int owner, int locked)
{
	struct snd_seq_queue *q;

	q = kzalloc(sizeof(*q), GFP_KERNEL);
	if (!q)
		return NULL;

	spin_lock_init(&q->owner_lock);
	spin_lock_init(&q->check_lock);
	mutex_init(&q->timer_mutex);
	snd_use_lock_init(&q->use_lock);
	q->queue = -1;

	q->tickq = snd_seq_prioq_new();
	q->timeq = snd_seq_prioq_new();
	q->timer = snd_seq_timer_new();
	if (q->tickq == NULL || q->timeq == NULL || q->timer == NULL) {
		snd_seq_prioq_delete(&q->tickq);
		snd_seq_prioq_delete(&q->timeq);
		snd_seq_timer_delete(&q->timer);
		kfree(q);
		return NULL;
	}

	q->owner = owner;
	q->locked = locked;
	q->klocked = 0;

	return q;
}