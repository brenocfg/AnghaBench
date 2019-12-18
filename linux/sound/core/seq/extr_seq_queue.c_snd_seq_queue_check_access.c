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
struct snd_seq_queue {int /*<<< orphan*/  owner_lock; } ;

/* Variables and functions */
 int check_access (struct snd_seq_queue*,int) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_queue_check_access(int queueid, int client)
{
	struct snd_seq_queue *q = queueptr(queueid);
	int access_ok;
	unsigned long flags;

	if (! q)
		return 0;
	spin_lock_irqsave(&q->owner_lock, flags);
	access_ok = check_access(q, client);
	spin_unlock_irqrestore(&q->owner_lock, flags);
	queuefree(q);
	return access_ok;
}