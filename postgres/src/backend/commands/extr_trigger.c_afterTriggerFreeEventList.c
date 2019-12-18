#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tailfree; int /*<<< orphan*/ * tail; TYPE_2__* head; } ;
typedef  TYPE_1__ AfterTriggerEventList ;
typedef  TYPE_2__ AfterTriggerEventChunk ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
afterTriggerFreeEventList(AfterTriggerEventList *events)
{
	AfterTriggerEventChunk *chunk;

	while ((chunk = events->head) != NULL)
	{
		events->head = chunk->next;
		pfree(chunk);
	}
	events->tail = NULL;
	events->tailfree = NULL;
}