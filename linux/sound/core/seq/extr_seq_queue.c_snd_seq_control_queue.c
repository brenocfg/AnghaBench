#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_queue {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {TYPE_1__ queue; } ;
struct snd_seq_event {TYPE_3__ source; TYPE_2__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  queue_access_lock (struct snd_seq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_access_unlock (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_queue_process_event (struct snd_seq_queue*,struct snd_seq_event*,int,int) ; 

int snd_seq_control_queue(struct snd_seq_event *ev, int atomic, int hop)
{
	struct snd_seq_queue *q;

	if (snd_BUG_ON(!ev))
		return -EINVAL;
	q = queueptr(ev->data.queue.queue);

	if (q == NULL)
		return -EINVAL;

	if (! queue_access_lock(q, ev->source.client)) {
		queuefree(q);
		return -EPERM;
	}

	snd_seq_queue_process_event(q, ev, atomic, hop);

	queue_access_unlock(q);
	queuefree(q);
	return 0;
}