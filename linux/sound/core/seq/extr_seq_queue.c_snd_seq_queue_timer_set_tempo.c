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
struct snd_seq_queue_tempo {scalar_t__ skew_base; int /*<<< orphan*/  skew_value; int /*<<< orphan*/  ppq; int /*<<< orphan*/  tempo; } ;
struct snd_seq_queue {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  queue_access_lock (struct snd_seq_queue*,int) ; 
 int /*<<< orphan*/  queue_access_unlock (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int snd_seq_timer_set_skew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int snd_seq_timer_set_tempo_ppq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_seq_queue_timer_set_tempo(int queueid, int client,
				  struct snd_seq_queue_tempo *info)
{
	struct snd_seq_queue *q = queueptr(queueid);
	int result;

	if (q == NULL)
		return -EINVAL;
	if (! queue_access_lock(q, client)) {
		queuefree(q);
		return -EPERM;
	}

	result = snd_seq_timer_set_tempo_ppq(q->timer, info->tempo, info->ppq);
	if (result >= 0 && info->skew_base > 0)
		result = snd_seq_timer_set_skew(q->timer, info->skew_value,
						info->skew_base);
	queue_access_unlock(q);
	queuefree(q);
	return result;
}