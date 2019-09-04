#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* entries; TYPE_1__* free; int /*<<< orphan*/ * qe; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_2__ MsgQueue_t ;

/* Variables and functions */
 int NR_MESSAGES ; 

void msgqueue_initialise(MsgQueue_t *msgq)
{
	int i;

	msgq->qe = NULL;
	msgq->free = &msgq->entries[0];

	for (i = 0; i < NR_MESSAGES; i++)
		msgq->entries[i].next = &msgq->entries[i + 1];

	msgq->entries[NR_MESSAGES - 1].next = NULL;
}