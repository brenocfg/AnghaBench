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
struct snd_seq_queue {int queue; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  num_queues ; 
 struct snd_seq_queue** queue_list ; 
 int /*<<< orphan*/  queue_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int queue_list_add(struct snd_seq_queue *q)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&queue_list_lock, flags);
	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if (! queue_list[i]) {
			queue_list[i] = q;
			q->queue = i;
			num_queues++;
			spin_unlock_irqrestore(&queue_list_lock, flags);
			return i;
		}
	}
	spin_unlock_irqrestore(&queue_list_lock, flags);
	return -1;
}