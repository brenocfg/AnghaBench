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
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ SHM_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShmemAddrIsValid (TYPE_1__*) ; 

void
SHMQueueDelete(SHM_QUEUE *queue)
{
	SHM_QUEUE  *nextElem = queue->next;
	SHM_QUEUE  *prevElem = queue->prev;

	Assert(ShmemAddrIsValid(queue));
	Assert(ShmemAddrIsValid(nextElem));
	Assert(ShmemAddrIsValid(prevElem));

	prevElem->next = queue->next;
	nextElem->prev = queue->prev;

	queue->prev = queue->next = NULL;
}