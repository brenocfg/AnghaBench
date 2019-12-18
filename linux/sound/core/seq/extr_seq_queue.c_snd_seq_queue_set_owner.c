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
struct snd_seq_queue {int locked; int owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  queue_access_lock (struct snd_seq_queue*,int) ; 
 int /*<<< orphan*/  queue_access_unlock (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 

int snd_seq_queue_set_owner(int queueid, int client, int locked)
{
	struct snd_seq_queue *q = queueptr(queueid);

	if (q == NULL)
		return -EINVAL;

	if (! queue_access_lock(q, client)) {
		queuefree(q);
		return -EPERM;
	}

	q->locked = locked ? 1 : 0;
	q->owner = client;
	queue_access_unlock(q);
	queuefree(q);

	return 0;
}