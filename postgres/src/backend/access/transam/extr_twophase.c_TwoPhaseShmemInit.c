#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pgprocno; } ;
struct TYPE_6__ {TYPE_1__* freeGXacts; scalar_t__ numPrepXacts; } ;
struct TYPE_5__ {scalar_t__ dummyBackendId; int /*<<< orphan*/  pgprocno; struct TYPE_5__* next; } ;
typedef  TYPE_1__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int MAXALIGN (scalar_t__) ; 
 scalar_t__ MaxBackends ; 
 TYPE_4__* PreparedXactProcs ; 
 TYPE_2__* ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TwoPhaseShmemSize () ; 
 TYPE_2__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateData ; 
 int max_prepared_xacts ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepXacts ; 

void
TwoPhaseShmemInit(void)
{
	bool		found;

	TwoPhaseState = ShmemInitStruct("Prepared Transaction Table",
									TwoPhaseShmemSize(),
									&found);
	if (!IsUnderPostmaster)
	{
		GlobalTransaction gxacts;
		int			i;

		Assert(!found);
		TwoPhaseState->freeGXacts = NULL;
		TwoPhaseState->numPrepXacts = 0;

		/*
		 * Initialize the linked list of free GlobalTransactionData structs
		 */
		gxacts = (GlobalTransaction)
			((char *) TwoPhaseState +
			 MAXALIGN(offsetof(TwoPhaseStateData, prepXacts) +
					  sizeof(GlobalTransaction) * max_prepared_xacts));
		for (i = 0; i < max_prepared_xacts; i++)
		{
			/* insert into linked list */
			gxacts[i].next = TwoPhaseState->freeGXacts;
			TwoPhaseState->freeGXacts = &gxacts[i];

			/* associate it with a PGPROC assigned by InitProcGlobal */
			gxacts[i].pgprocno = PreparedXactProcs[i].pgprocno;

			/*
			 * Assign a unique ID for each dummy proc, so that the range of
			 * dummy backend IDs immediately follows the range of normal
			 * backend IDs. We don't dare to assign a real backend ID to dummy
			 * procs, because prepared transactions don't take part in cache
			 * invalidation like a real backend ID would imply, but having a
			 * unique ID for them is nevertheless handy. This arrangement
			 * allows you to allocate an array of size (MaxBackends +
			 * max_prepared_xacts + 1), and have a slot for every backend and
			 * prepared transaction. Currently multixact.c uses that
			 * technique.
			 */
			gxacts[i].dummyBackendId = MaxBackends + 1 + i;
		}
	}
	else
		Assert(found);
}