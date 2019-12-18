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
struct snd_seq_queue {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_timer_close (struct snd_seq_queue*) ; 

int snd_seq_queue_timer_close(int queueid)
{
	struct snd_seq_queue *queue;
	int result = 0;

	queue = queueptr(queueid);
	if (queue == NULL)
		return -EINVAL;
	snd_seq_timer_close(queue);
	queuefree(queue);
	return result;
}