#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msgqueue_entry {struct msgqueue_entry* next; } ;
struct TYPE_3__ {struct msgqueue_entry* free; } ;
typedef  TYPE_1__ MsgQueue_t ;

/* Variables and functions */

__attribute__((used)) static struct msgqueue_entry *mqe_alloc(MsgQueue_t *msgq)
{
	struct msgqueue_entry *mq;

	if ((mq = msgq->free) != NULL)
		msgq->free = mq->next;

	return mq;
}