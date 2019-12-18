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
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  queue_delete (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queue_list_remove (int,int) ; 

int snd_seq_queue_delete(int client, int queueid)
{
	struct snd_seq_queue *q;

	if (queueid < 0 || queueid >= SNDRV_SEQ_MAX_QUEUES)
		return -EINVAL;
	q = queue_list_remove(queueid, client);
	if (q == NULL)
		return -EINVAL;
	queue_delete(q);

	return 0;
}