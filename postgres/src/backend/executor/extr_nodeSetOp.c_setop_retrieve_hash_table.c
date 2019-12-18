#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {int /*<<< orphan*/  firstTuple; scalar_t__ additional; } ;
typedef  TYPE_2__ TupleHashEntryData ;
struct TYPE_7__ {int /*<<< orphan*/ * ps_ResultTupleSlot; } ;
struct TYPE_9__ {int setop_done; scalar_t__ numOutput; int /*<<< orphan*/  hashiter; int /*<<< orphan*/  hashtable; TYPE_1__ ps; } ;
typedef  int /*<<< orphan*/  SetOpStatePerGroup ;
typedef  TYPE_3__ SetOpState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ScanTupleHashTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_output_count (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
setop_retrieve_hash_table(SetOpState *setopstate)
{
	TupleHashEntryData *entry;
	TupleTableSlot *resultTupleSlot;

	/*
	 * get state info from node
	 */
	resultTupleSlot = setopstate->ps.ps_ResultTupleSlot;

	/*
	 * We loop retrieving groups until we find one we should return
	 */
	while (!setopstate->setop_done)
	{
		CHECK_FOR_INTERRUPTS();

		/*
		 * Find the next entry in the hash table
		 */
		entry = ScanTupleHashTable(setopstate->hashtable, &setopstate->hashiter);
		if (entry == NULL)
		{
			/* No more entries in hashtable, so done */
			setopstate->setop_done = true;
			return NULL;
		}

		/*
		 * See if we should emit any copies of this tuple, and if so return
		 * the first copy.
		 */
		set_output_count(setopstate, (SetOpStatePerGroup) entry->additional);

		if (setopstate->numOutput > 0)
		{
			setopstate->numOutput--;
			return ExecStoreMinimalTuple(entry->firstTuple,
										 resultTupleSlot,
										 false);
		}
	}

	/* No more groups */
	ExecClearTuple(resultTupleSlot);
	return NULL;
}