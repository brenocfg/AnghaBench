#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  TYPE_1__* TupleHashTable ;
typedef  int /*<<< orphan*/  TupleHashIterator ;
typedef  TYPE_2__* TupleHashEntry ;
struct TYPE_8__ {int /*<<< orphan*/  firstTuple; } ;
struct TYPE_7__ {int numCols; int /*<<< orphan*/  tempcxt; int /*<<< orphan*/  tab_collations; int /*<<< orphan*/  tableslot; int /*<<< orphan*/ * keyColIdx; } ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitTupleHashIterator (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ScanTupleHashTable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TermTupleHashIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  execTuplesUnequal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
findPartialMatch(TupleHashTable hashtable, TupleTableSlot *slot,
				 FmgrInfo *eqfunctions)
{
	int			numCols = hashtable->numCols;
	AttrNumber *keyColIdx = hashtable->keyColIdx;
	TupleHashIterator hashiter;
	TupleHashEntry entry;

	InitTupleHashIterator(hashtable, &hashiter);
	while ((entry = ScanTupleHashTable(hashtable, &hashiter)) != NULL)
	{
		CHECK_FOR_INTERRUPTS();

		ExecStoreMinimalTuple(entry->firstTuple, hashtable->tableslot, false);
		if (!execTuplesUnequal(slot, hashtable->tableslot,
							   numCols, keyColIdx,
							   eqfunctions,
							   hashtable->tab_collations,
							   hashtable->tempcxt))
		{
			TermTupleHashIterator(&hashiter);
			return true;
		}
	}
	/* No TermTupleHashIterator call needed here */
	return false;
}