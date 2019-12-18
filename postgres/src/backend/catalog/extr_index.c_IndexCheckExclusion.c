#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_15__ {int /*<<< orphan*/  ecxt_per_tuple_memory; TYPE_1__* ecxt_scantuple; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ii_PredicateState; int /*<<< orphan*/  ii_ExpressionsState; int /*<<< orphan*/  ii_Predicate; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ IndexInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_3__ ExprContext ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (TYPE_1__*) ; 
 int /*<<< orphan*/ * ExecPrepareQual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecQual (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FormIndexDatum (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 TYPE_3__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ ReindexIsCurrentlyProcessingIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetReindexProcessing () ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_exclusion_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  table_beginscan_strat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 scalar_t__ table_scan_getnextslot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* table_slot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
IndexCheckExclusion(Relation heapRelation,
					Relation indexRelation,
					IndexInfo *indexInfo)
{
	TableScanDesc scan;
	Datum		values[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	ExprState  *predicate;
	TupleTableSlot *slot;
	EState	   *estate;
	ExprContext *econtext;
	Snapshot	snapshot;

	/*
	 * If we are reindexing the target index, mark it as no longer being
	 * reindexed, to forestall an Assert in index_beginscan when we try to use
	 * the index for probes.  This is OK because the index is now fully valid.
	 */
	if (ReindexIsCurrentlyProcessingIndex(RelationGetRelid(indexRelation)))
		ResetReindexProcessing();

	/*
	 * Need an EState for evaluation of index expressions and partial-index
	 * predicates.  Also a slot to hold the current tuple.
	 */
	estate = CreateExecutorState();
	econtext = GetPerTupleExprContext(estate);
	slot = table_slot_create(heapRelation, NULL);

	/* Arrange for econtext's scan tuple to be the tuple under test */
	econtext->ecxt_scantuple = slot;

	/* Set up execution state for predicate, if any. */
	predicate = ExecPrepareQual(indexInfo->ii_Predicate, estate);

	/*
	 * Scan all live tuples in the base relation.
	 */
	snapshot = RegisterSnapshot(GetLatestSnapshot());
	scan = table_beginscan_strat(heapRelation,	/* relation */
								 snapshot,	/* snapshot */
								 0, /* number of keys */
								 NULL,	/* scan key */
								 true,	/* buffer access strategy OK */
								 true); /* syncscan OK */

	while (table_scan_getnextslot(scan, ForwardScanDirection, slot))
	{
		CHECK_FOR_INTERRUPTS();

		/*
		 * In a partial index, ignore tuples that don't satisfy the predicate.
		 */
		if (predicate != NULL)
		{
			if (!ExecQual(predicate, econtext))
				continue;
		}

		/*
		 * Extract index column values, including computing expressions.
		 */
		FormIndexDatum(indexInfo,
					   slot,
					   estate,
					   values,
					   isnull);

		/*
		 * Check that this tuple has no conflicts.
		 */
		check_exclusion_constraint(heapRelation,
								   indexRelation, indexInfo,
								   &(slot->tts_tid), values, isnull,
								   estate, true);

		MemoryContextReset(econtext->ecxt_per_tuple_memory);
	}

	table_endscan(scan);
	UnregisterSnapshot(snapshot);

	ExecDropSingleTupleTableSlot(slot);

	FreeExecutorState(estate);

	/* These may have been pointing to the now-gone estate */
	indexInfo->ii_ExpressionsState = NIL;
	indexInfo->ii_PredicateState = NULL;
}