#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ SHM_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShmemAddrIsValid (TYPE_1__*) ; 

void
SHMQueueInsertBefore(SHM_QUEUE *queue, SHM_QUEUE *elem)
{
	SHM_QUEUE  *prevPtr = queue->prev;

	Assert(ShmemAddrIsValid(queue));
	Assert(ShmemAddrIsValid(elem));

	elem->next = prevPtr->next;
	elem->prev = queue->prev;
	queue->prev = elem;
	prevPtr->next = elem;
}