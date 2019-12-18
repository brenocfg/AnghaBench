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
struct snd_seq_queue {int /*<<< orphan*/  queue; int /*<<< orphan*/  timeq; int /*<<< orphan*/  tickq; int /*<<< orphan*/  clients_bitmap; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  queue_delete (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queue_list_remove (int,int) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 int /*<<< orphan*/  snd_seq_prioq_leave (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_queue_use (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void snd_seq_queue_client_leave(int client)
{
	int i;
	struct snd_seq_queue *q;

	/* delete own queues from queue list */
	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queue_list_remove(i, client)) != NULL)
			queue_delete(q);
	}

	/* remove cells from existing queues -
	 * they are not owned by this client
	 */
	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queueptr(i)) == NULL)
			continue;
		if (test_bit(client, q->clients_bitmap)) {
			snd_seq_prioq_leave(q->tickq, client, 0);
			snd_seq_prioq_leave(q->timeq, client, 0);
			snd_seq_queue_use(q->queue, client, 0);
		}
		queuefree(q);
	}
}