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
struct snd_seq_queue {int /*<<< orphan*/  use_lock; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 struct snd_seq_queue** queue_list ; 
 int /*<<< orphan*/  queue_list_lock ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct snd_seq_queue *queueptr(int queueid)
{
	struct snd_seq_queue *q;
	unsigned long flags;

	if (queueid < 0 || queueid >= SNDRV_SEQ_MAX_QUEUES)
		return NULL;
	spin_lock_irqsave(&queue_list_lock, flags);
	q = queue_list[queueid];
	if (q)
		snd_use_lock_use(&q->use_lock);
	spin_unlock_irqrestore(&queue_list_lock, flags);
	return q;
}