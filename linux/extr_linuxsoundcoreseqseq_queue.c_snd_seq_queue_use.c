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
struct snd_seq_queue {int /*<<< orphan*/  timer_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_use (struct snd_seq_queue*,int,int) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 

int snd_seq_queue_use(int queueid, int client, int use)
{
	struct snd_seq_queue *queue;

	queue = queueptr(queueid);
	if (queue == NULL)
		return -EINVAL;
	mutex_lock(&queue->timer_mutex);
	queue_use(queue, client, use);
	mutex_unlock(&queue->timer_mutex);
	queuefree(queue);
	return 0;
}