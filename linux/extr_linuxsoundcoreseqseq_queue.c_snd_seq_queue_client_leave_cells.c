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
struct snd_seq_queue {int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_prioq_leave (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void snd_seq_queue_client_leave_cells(int client)
{
	int i;
	struct snd_seq_queue *q;

	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queueptr(i)) == NULL)
			continue;
		snd_seq_prioq_leave(q->tickq, client, 0);
		snd_seq_prioq_leave(q->timeq, client, 0);
		queuefree(q);
	}
}