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
struct snd_seq_remove_events {int remove_mode; scalar_t__ queue; } ;
struct snd_seq_queue {scalar_t__ queue; int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; int /*<<< orphan*/  clients_bitmap; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int SNDRV_SEQ_REMOVE_DEST ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_prioq_remove_events (int /*<<< orphan*/ ,int,struct snd_seq_remove_events*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void snd_seq_queue_remove_cells(int client, struct snd_seq_remove_events *info)
{
	int i;
	struct snd_seq_queue *q;

	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queueptr(i)) == NULL)
			continue;
		if (test_bit(client, q->clients_bitmap) &&
		    (! (info->remove_mode & SNDRV_SEQ_REMOVE_DEST) ||
		     q->queue == info->queue)) {
			snd_seq_prioq_remove_events(q->tickq, client, info);
			snd_seq_prioq_remove_events(q->timeq, client, info);
		}
		queuefree(q);
	}
}