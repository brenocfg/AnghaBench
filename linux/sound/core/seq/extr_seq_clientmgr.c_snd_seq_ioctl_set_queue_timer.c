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
struct snd_seq_timer {scalar_t__ type; int /*<<< orphan*/  preferred_resolution; int /*<<< orphan*/  alsa_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  resolution; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ alsa; } ;
struct snd_seq_queue_timer {scalar_t__ type; int /*<<< orphan*/  queue; TYPE_2__ u; } ;
struct snd_seq_queue {int /*<<< orphan*/  timer_mutex; struct snd_seq_timer* timer; } ;
struct snd_seq_client {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EPERM ; 
 scalar_t__ SNDRV_SEQ_TIMER_ALSA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_seq_queue_check_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_queue_timer_close (int /*<<< orphan*/ ) ; 
 int snd_seq_queue_timer_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_seq_ioctl_set_queue_timer(struct snd_seq_client *client,
					 void *arg)
{
	struct snd_seq_queue_timer *timer = arg;
	int result = 0;

	if (timer->type != SNDRV_SEQ_TIMER_ALSA)
		return -EINVAL;

	if (snd_seq_queue_check_access(timer->queue, client->number)) {
		struct snd_seq_queue *q;
		struct snd_seq_timer *tmr;

		q = queueptr(timer->queue);
		if (q == NULL)
			return -ENXIO;
		mutex_lock(&q->timer_mutex);
		tmr = q->timer;
		snd_seq_queue_timer_close(timer->queue);
		tmr->type = timer->type;
		if (tmr->type == SNDRV_SEQ_TIMER_ALSA) {
			tmr->alsa_id = timer->u.alsa.id;
			tmr->preferred_resolution = timer->u.alsa.resolution;
		}
		result = snd_seq_queue_timer_open(timer->queue);
		mutex_unlock(&q->timer_mutex);
		queuefree(q);
	} else {
		return -EPERM;
	}	

	return result;
}