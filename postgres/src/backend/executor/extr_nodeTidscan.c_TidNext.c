#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {TYPE_4__* state; } ;
struct TYPE_8__ {int /*<<< orphan*/  ss_currentScanDesc; int /*<<< orphan*/ * ss_ScanTupleSlot; int /*<<< orphan*/  ss_currentRelation; TYPE_1__ ps; } ;
struct TYPE_9__ {int tss_NumTids; int tss_TidPtr; scalar_t__ tss_isCurrentOf; int /*<<< orphan*/ * tss_TidList; TYPE_2__ ss; } ;
typedef  TYPE_3__ TidScanState ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_10__ {int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_direction; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_4__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TidListEval (TYPE_3__*) ; 
 scalar_t__ table_tuple_fetch_row_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_tuple_get_latest_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
TidNext(TidScanState *node)
{
	EState	   *estate;
	ScanDirection direction;
	Snapshot	snapshot;
	TableScanDesc scan;
	Relation	heapRelation;
	TupleTableSlot *slot;
	ItemPointerData *tidList;
	int			numTids;
	bool		bBackward;

	/*
	 * extract necessary information from tid scan node
	 */
	estate = node->ss.ps.state;
	direction = estate->es_direction;
	snapshot = estate->es_snapshot;
	heapRelation = node->ss.ss_currentRelation;
	slot = node->ss.ss_ScanTupleSlot;

	/*
	 * First time through, compute the list of TIDs to be visited
	 */
	if (node->tss_TidList == NULL)
		TidListEval(node);

	scan = node->ss.ss_currentScanDesc;
	tidList = node->tss_TidList;
	numTids = node->tss_NumTids;

	/*
	 * Initialize or advance scan position, depending on direction.
	 */
	bBackward = ScanDirectionIsBackward(direction);
	if (bBackward)
	{
		if (node->tss_TidPtr < 0)
		{
			/* initialize for backward scan */
			node->tss_TidPtr = numTids - 1;
		}
		else
			node->tss_TidPtr--;
	}
	else
	{
		if (node->tss_TidPtr < 0)
		{
			/* initialize for forward scan */
			node->tss_TidPtr = 0;
		}
		else
			node->tss_TidPtr++;
	}

	while (node->tss_TidPtr >= 0 && node->tss_TidPtr < numTids)
	{
		ItemPointerData tid = tidList[node->tss_TidPtr];

		/*
		 * For WHERE CURRENT OF, the tuple retrieved from the cursor might
		 * since have been updated; if so, we should fetch the version that is
		 * current according to our snapshot.
		 */
		if (node->tss_isCurrentOf)
			table_tuple_get_latest_tid(scan, &tid);

		if (table_tuple_fetch_row_version(heapRelation, &tid, snapshot, slot))
			return slot;

		/* Bad TID or failed snapshot qual; try next */
		if (bBackward)
			node->tss_TidPtr--;
		else
			node->tss_TidPtr++;

		CHECK_FOR_INTERRUPTS();
	}

	/*
	 * if we get here it means the tid scan failed so we are at the end of the
	 * scan..
	 */
	return ExecClearTuple(slot);
}