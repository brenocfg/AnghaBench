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
struct snd_seq_timer {int dummy; } ;
struct snd_seq_queue {struct snd_seq_timer* timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_timer_defaults (struct snd_seq_timer*) ; 
 int snd_seq_timer_open (struct snd_seq_queue*) ; 

int snd_seq_queue_timer_open(int queueid)
{
	int result = 0;
	struct snd_seq_queue *queue;
	struct snd_seq_timer *tmr;

	queue = queueptr(queueid);
	if (queue == NULL)
		return -EINVAL;
	tmr = queue->timer;
	if ((result = snd_seq_timer_open(queue)) < 0) {
		snd_seq_timer_defaults(tmr);
		result = snd_seq_timer_open(queue);
	}
	queuefree(queue);
	return result;
}