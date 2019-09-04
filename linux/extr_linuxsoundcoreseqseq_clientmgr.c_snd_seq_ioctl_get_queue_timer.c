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
struct snd_seq_queue_timer {scalar_t__ type; TYPE_2__ u; int /*<<< orphan*/  queue; } ;
struct snd_seq_queue {int /*<<< orphan*/  timer_mutex; int /*<<< orphan*/  queue; struct snd_seq_timer* timer; } ;
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_SEQ_TIMER_ALSA ; 
 int /*<<< orphan*/  memset (struct snd_seq_queue_timer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_seq_ioctl_get_queue_timer(struct snd_seq_client *client,
					 void *arg)
{
	struct snd_seq_queue_timer *timer = arg;
	struct snd_seq_queue *queue;
	struct snd_seq_timer *tmr;

	queue = queueptr(timer->queue);
	if (queue == NULL)
		return -EINVAL;

	mutex_lock(&queue->timer_mutex);
	tmr = queue->timer;
	memset(timer, 0, sizeof(*timer));
	timer->queue = queue->queue;

	timer->type = tmr->type;
	if (tmr->type == SNDRV_SEQ_TIMER_ALSA) {
		timer->u.alsa.id = tmr->alsa_id;
		timer->u.alsa.resolution = tmr->preferred_resolution;
	}
	mutex_unlock(&queue->timer_mutex);
	queuefree(queue);
	
	return 0;
}