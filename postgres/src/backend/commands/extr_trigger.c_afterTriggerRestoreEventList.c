#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; } ;
struct TYPE_9__ {int /*<<< orphan*/  tailfree; TYPE_1__* tail; } ;
struct TYPE_8__ {int /*<<< orphan*/  freeptr; TYPE_3__* next; } ;
typedef  TYPE_2__ AfterTriggerEventList ;
typedef  TYPE_3__ AfterTriggerEventChunk ;

/* Variables and functions */
 int /*<<< orphan*/  afterTriggerFreeEventList (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static void
afterTriggerRestoreEventList(AfterTriggerEventList *events,
							 const AfterTriggerEventList *old_events)
{
	AfterTriggerEventChunk *chunk;
	AfterTriggerEventChunk *next_chunk;

	if (old_events->tail == NULL)
	{
		/* restoring to a completely empty state, so free everything */
		afterTriggerFreeEventList(events);
	}
	else
	{
		*events = *old_events;
		/* free any chunks after the last one we want to keep */
		for (chunk = events->tail->next; chunk != NULL; chunk = next_chunk)
		{
			next_chunk = chunk->next;
			pfree(chunk);
		}
		/* and clean up the tail chunk to be the right length */
		events->tail->next = NULL;
		events->tail->freeptr = events->tailfree;

		/*
		 * We don't make any effort to remove now-unused shared data records.
		 * They might still be useful, anyway.
		 */
	}
}