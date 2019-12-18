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
struct TYPE_3__ {int nestLevel; int atCommit; scalar_t__ backend; int /*<<< orphan*/  relnode; struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  TYPE_1__ PendingRelDelete ;

/* Variables and functions */
 int GetCurrentTransactionNestLevel () ; 
 scalar_t__ InvalidBackendId ; 
 scalar_t__ palloc (int) ; 
 TYPE_1__* pendingDeletes ; 

int
smgrGetPendingDeletes(bool forCommit, RelFileNode **ptr)
{
	int			nestLevel = GetCurrentTransactionNestLevel();
	int			nrels;
	RelFileNode *rptr;
	PendingRelDelete *pending;

	nrels = 0;
	for (pending = pendingDeletes; pending != NULL; pending = pending->next)
	{
		if (pending->nestLevel >= nestLevel && pending->atCommit == forCommit
			&& pending->backend == InvalidBackendId)
			nrels++;
	}
	if (nrels == 0)
	{
		*ptr = NULL;
		return 0;
	}
	rptr = (RelFileNode *) palloc(nrels * sizeof(RelFileNode));
	*ptr = rptr;
	for (pending = pendingDeletes; pending != NULL; pending = pending->next)
	{
		if (pending->nestLevel >= nestLevel && pending->atCommit == forCommit
			&& pending->backend == InvalidBackendId)
		{
			*rptr = pending->relnode;
			rptr++;
		}
	}
	return nrels;
}