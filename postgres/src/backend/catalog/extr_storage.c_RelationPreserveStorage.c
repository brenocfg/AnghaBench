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
struct TYPE_4__ {int atCommit; struct TYPE_4__* next; int /*<<< orphan*/  relnode; } ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  TYPE_1__ PendingRelDelete ;

/* Variables and functions */
 scalar_t__ RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pendingDeletes ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
RelationPreserveStorage(RelFileNode rnode, bool atCommit)
{
	PendingRelDelete *pending;
	PendingRelDelete *prev;
	PendingRelDelete *next;

	prev = NULL;
	for (pending = pendingDeletes; pending != NULL; pending = next)
	{
		next = pending->next;
		if (RelFileNodeEquals(rnode, pending->relnode)
			&& pending->atCommit == atCommit)
		{
			/* unlink and delete list entry */
			if (prev)
				prev->next = next;
			else
				pendingDeletes = next;
			pfree(pending);
			/* prev does not change */
		}
		else
		{
			/* unrelated entry, don't touch it */
			prev = pending;
		}
	}
}