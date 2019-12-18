#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_28__ {int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_direction; } ;
struct TYPE_27__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_26__ {int /*<<< orphan*/  indexorderdir; } ;
struct TYPE_25__ {int* xs_orderbynulls; int /*<<< orphan*/ * xs_orderbyvals; scalar_t__ xs_recheckorderby; scalar_t__ xs_recheck; } ;
struct TYPE_21__ {TYPE_7__* ps_ExprContext; scalar_t__ plan; TYPE_8__* state; } ;
struct TYPE_22__ {int /*<<< orphan*/  ss_currentRelation; int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_24__ {scalar_t__ iss_NumRuntimeKeys; int iss_ReachedEnd; int* iss_OrderByNulls; int /*<<< orphan*/ * iss_OrderByValues; int /*<<< orphan*/  indexqualorig; int /*<<< orphan*/  iss_ReorderQueue; int /*<<< orphan*/  iss_NumOrderByKeys; int /*<<< orphan*/  iss_OrderByKeys; int /*<<< orphan*/  iss_NumScanKeys; int /*<<< orphan*/  iss_ScanKeys; scalar_t__ iss_RuntimeKeysReady; TYPE_5__* iss_ScanDesc; int /*<<< orphan*/  iss_RelationDesc; TYPE_2__ ss; } ;
struct TYPE_23__ {int* orderbynulls; int /*<<< orphan*/ * orderbyvals; } ;
typedef  TYPE_3__ ReorderTuple ;
typedef  TYPE_4__ IndexScanState ;
typedef  TYPE_5__* IndexScanDesc ;
typedef  TYPE_6__ IndexScan ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_7__ ExprContext ;
typedef  TYPE_8__ EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EvalOrderByExpressions (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  InstrCountFiltered2 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_7__*) ; 
 int /*<<< orphan*/  ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int cmp_orderbyvals (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getnext_slot (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_rescan (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pairingheap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reorderqueue_pop (TYPE_4__*) ; 
 int /*<<< orphan*/  reorderqueue_push (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static TupleTableSlot *
IndexNextWithReorder(IndexScanState *node)
{
	EState	   *estate;
	ExprContext *econtext;
	IndexScanDesc scandesc;
	TupleTableSlot *slot;
	ReorderTuple *topmost = NULL;
	bool		was_exact;
	Datum	   *lastfetched_vals;
	bool	   *lastfetched_nulls;
	int			cmp;

	estate = node->ss.ps.state;

	/*
	 * Only forward scan is supported with reordering.  Note: we can get away
	 * with just Asserting here because the system will not try to run the
	 * plan backwards if ExecSupportsBackwardScan() says it won't work.
	 * Currently, that is guaranteed because no index AMs support both
	 * amcanorderbyop and amcanbackward; if any ever do,
	 * ExecSupportsBackwardScan() will need to consider indexorderbys
	 * explicitly.
	 */
	Assert(!ScanDirectionIsBackward(((IndexScan *) node->ss.ps.plan)->indexorderdir));
	Assert(ScanDirectionIsForward(estate->es_direction));

	scandesc = node->iss_ScanDesc;
	econtext = node->ss.ps.ps_ExprContext;
	slot = node->ss.ss_ScanTupleSlot;

	if (scandesc == NULL)
	{
		/*
		 * We reach here if the index scan is not parallel, or if we're
		 * serially executing an index scan that was planned to be parallel.
		 */
		scandesc = index_beginscan(node->ss.ss_currentRelation,
								   node->iss_RelationDesc,
								   estate->es_snapshot,
								   node->iss_NumScanKeys,
								   node->iss_NumOrderByKeys);

		node->iss_ScanDesc = scandesc;

		/*
		 * If no run-time keys to calculate or they are ready, go ahead and
		 * pass the scankeys to the index AM.
		 */
		if (node->iss_NumRuntimeKeys == 0 || node->iss_RuntimeKeysReady)
			index_rescan(scandesc,
						 node->iss_ScanKeys, node->iss_NumScanKeys,
						 node->iss_OrderByKeys, node->iss_NumOrderByKeys);
	}

	for (;;)
	{
		CHECK_FOR_INTERRUPTS();

		/*
		 * Check the reorder queue first.  If the topmost tuple in the queue
		 * has an ORDER BY value smaller than (or equal to) the value last
		 * returned by the index, we can return it now.
		 */
		if (!pairingheap_is_empty(node->iss_ReorderQueue))
		{
			topmost = (ReorderTuple *) pairingheap_first(node->iss_ReorderQueue);

			if (node->iss_ReachedEnd ||
				cmp_orderbyvals(topmost->orderbyvals,
								topmost->orderbynulls,
								scandesc->xs_orderbyvals,
								scandesc->xs_orderbynulls,
								node) <= 0)
			{
				HeapTuple	tuple;

				tuple = reorderqueue_pop(node);

				/* Pass 'true', as the tuple in the queue is a palloc'd copy */
				ExecForceStoreHeapTuple(tuple, slot, true);
				return slot;
			}
		}
		else if (node->iss_ReachedEnd)
		{
			/* Queue is empty, and no more tuples from index.  We're done. */
			return ExecClearTuple(slot);
		}

		/*
		 * Fetch next tuple from the index.
		 */
next_indextuple:
		if (!index_getnext_slot(scandesc, ForwardScanDirection, slot))
		{
			/*
			 * No more tuples from the index.  But we still need to drain any
			 * remaining tuples from the queue before we're done.
			 */
			node->iss_ReachedEnd = true;
			continue;
		}

		/*
		 * If the index was lossy, we have to recheck the index quals and
		 * ORDER BY expressions using the fetched tuple.
		 */
		if (scandesc->xs_recheck)
		{
			econtext->ecxt_scantuple = slot;
			if (!ExecQualAndReset(node->indexqualorig, econtext))
			{
				/* Fails recheck, so drop it and loop back for another */
				InstrCountFiltered2(node, 1);
				/* allow this loop to be cancellable */
				CHECK_FOR_INTERRUPTS();
				goto next_indextuple;
			}
		}

		if (scandesc->xs_recheckorderby)
		{
			econtext->ecxt_scantuple = slot;
			ResetExprContext(econtext);
			EvalOrderByExpressions(node, econtext);

			/*
			 * Was the ORDER BY value returned by the index accurate?  The
			 * recheck flag means that the index can return inaccurate values,
			 * but then again, the value returned for any particular tuple
			 * could also be exactly correct.  Compare the value returned by
			 * the index with the recalculated value.  (If the value returned
			 * by the index happened to be exact right, we can often avoid
			 * pushing the tuple to the queue, just to pop it back out again.)
			 */
			cmp = cmp_orderbyvals(node->iss_OrderByValues,
								  node->iss_OrderByNulls,
								  scandesc->xs_orderbyvals,
								  scandesc->xs_orderbynulls,
								  node);
			if (cmp < 0)
				elog(ERROR, "index returned tuples in wrong order");
			else if (cmp == 0)
				was_exact = true;
			else
				was_exact = false;
			lastfetched_vals = node->iss_OrderByValues;
			lastfetched_nulls = node->iss_OrderByNulls;
		}
		else
		{
			was_exact = true;
			lastfetched_vals = scandesc->xs_orderbyvals;
			lastfetched_nulls = scandesc->xs_orderbynulls;
		}

		/*
		 * Can we return this tuple immediately, or does it need to be pushed
		 * to the reorder queue?  If the ORDER BY expression values returned
		 * by the index were inaccurate, we can't return it yet, because the
		 * next tuple from the index might need to come before this one. Also,
		 * we can't return it yet if there are any smaller tuples in the queue
		 * already.
		 */
		if (!was_exact || (topmost && cmp_orderbyvals(lastfetched_vals,
													  lastfetched_nulls,
													  topmost->orderbyvals,
													  topmost->orderbynulls,
													  node) > 0))
		{
			/* Put this tuple to the queue */
			reorderqueue_push(node, slot, lastfetched_vals, lastfetched_nulls);
			continue;
		}
		else
		{
			/* Can return this tuple immediately. */
			return slot;
		}
	}

	/*
	 * if we get here it means the index scan failed so we are at the end of
	 * the scan..
	 */
	return ExecClearTuple(slot);
}