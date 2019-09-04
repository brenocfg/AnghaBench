#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msgqueue_entry {struct msgqueue_entry* next; } ;
struct TYPE_4__ {struct msgqueue_entry* qe; } ;
typedef  TYPE_1__ MsgQueue_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqe_free (TYPE_1__*,struct msgqueue_entry*) ; 

void msgqueue_flush(MsgQueue_t *msgq)
{
	struct msgqueue_entry *mq, *mqnext;

	for (mq = msgq->qe; mq; mq = mqnext) {
		mqnext = mq->next;
		mqe_free(msgq, mq);
	}
	msgq->qe = NULL;
}