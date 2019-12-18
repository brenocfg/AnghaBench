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
struct snd_seq_queue {int klocked; int /*<<< orphan*/  owner_lock; } ;

/* Variables and functions */
 int check_access (struct snd_seq_queue*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int queue_access_lock(struct snd_seq_queue *q, int client)
{
	unsigned long flags;
	int access_ok;
	
	spin_lock_irqsave(&q->owner_lock, flags);
	access_ok = check_access(q, client);
	if (access_ok)
		q->klocked = 1;
	spin_unlock_irqrestore(&q->owner_lock, flags);
	return access_ok;
}