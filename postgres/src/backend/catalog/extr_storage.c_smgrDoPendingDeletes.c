#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nestLevel; int atCommit; int /*<<< orphan*/  backend; int /*<<< orphan*/  relnode; struct TYPE_11__* next; } ;
typedef  TYPE_1__ SMgrRelation ;
typedef  TYPE_1__ PendingRelDelete ;

/* Variables and functions */
 int GetCurrentTransactionNestLevel () ; 
 TYPE_1__* palloc (int) ; 
 TYPE_1__* pendingDeletes ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_1__* repalloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  smgrclose (TYPE_1__) ; 
 int /*<<< orphan*/  smgrdounlinkall (TYPE_1__*,int,int) ; 
 TYPE_1__ smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
smgrDoPendingDeletes(bool isCommit)
{
	int			nestLevel = GetCurrentTransactionNestLevel();
	PendingRelDelete *pending;
	PendingRelDelete *prev;
	PendingRelDelete *next;
	int			nrels = 0,
				i = 0,
				maxrels = 0;
	SMgrRelation *srels = NULL;

	prev = NULL;
	for (pending = pendingDeletes; pending != NULL; pending = next)
	{
		next = pending->next;
		if (pending->nestLevel < nestLevel)
		{
			/* outer-level entries should not be processed yet */
			prev = pending;
		}
		else
		{
			/* unlink list entry first, so we don't retry on failure */
			if (prev)
				prev->next = next;
			else
				pendingDeletes = next;
			/* do deletion if called for */
			if (pending->atCommit == isCommit)
			{
				SMgrRelation srel;

				srel = smgropen(pending->relnode, pending->backend);

				/* allocate the initial array, or extend it, if needed */
				if (maxrels == 0)
				{
					maxrels = 8;
					srels = palloc(sizeof(SMgrRelation) * maxrels);
				}
				else if (maxrels <= nrels)
				{
					maxrels *= 2;
					srels = repalloc(srels, sizeof(SMgrRelation) * maxrels);
				}

				srels[nrels++] = srel;
			}
			/* must explicitly free the list entry */
			pfree(pending);
			/* prev does not change */
		}
	}

	if (nrels > 0)
	{
		smgrdounlinkall(srels, nrels, false);

		for (i = 0; i < nrels; i++)
			smgrclose(srels[i]);

		pfree(srels);
	}
}