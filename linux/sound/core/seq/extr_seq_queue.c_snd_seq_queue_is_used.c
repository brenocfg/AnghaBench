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
struct snd_seq_queue {int /*<<< orphan*/  clients_bitmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int snd_seq_queue_is_used(int queueid, int client)
{
	struct snd_seq_queue *q;
	int result;

	q = queueptr(queueid);
	if (q == NULL)
		return -EINVAL; /* invalid queue */
	result = test_bit(client, q->clients_bitmap) ? 1 : 0;
	queuefree(q);
	return result;
}