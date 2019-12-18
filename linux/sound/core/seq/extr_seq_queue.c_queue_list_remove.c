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
struct snd_seq_queue {int owner; int klocked; int /*<<< orphan*/  owner_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  num_queues ; 
 struct snd_seq_queue** queue_list ; 
 int /*<<< orphan*/  queue_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct snd_seq_queue *queue_list_remove(int id, int client)
{
	struct snd_seq_queue *q;
	unsigned long flags;

	spin_lock_irqsave(&queue_list_lock, flags);
	q = queue_list[id];
	if (q) {
		spin_lock(&q->owner_lock);
		if (q->owner == client) {
			/* found */
			q->klocked = 1;
			spin_unlock(&q->owner_lock);
			queue_list[id] = NULL;
			num_queues--;
			spin_unlock_irqrestore(&queue_list_lock, flags);
			return q;
		}
		spin_unlock(&q->owner_lock);
	}
	spin_unlock_irqrestore(&queue_list_lock, flags);
	return NULL;
}