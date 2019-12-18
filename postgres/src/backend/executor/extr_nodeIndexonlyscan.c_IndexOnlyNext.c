#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {TYPE_3__* tts_tupleDescriptor; } ;
typedef  TYPE_5__ TupleTableSlot ;
struct TYPE_34__ {TYPE_5__* ecxt_scantuple; } ;
struct TYPE_33__ {int /*<<< orphan*/  indexorderdir; } ;
struct TYPE_26__ {TYPE_9__* ps_ExprContext; scalar_t__ plan; TYPE_10__* state; } ;
struct TYPE_27__ {int /*<<< orphan*/  ss_currentRelation; TYPE_5__* ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_32__ {scalar_t__ ioss_NumRuntimeKeys; int /*<<< orphan*/  indexqual; TYPE_5__* ioss_TableSlot; int /*<<< orphan*/  ioss_VMBuffer; int /*<<< orphan*/  ioss_NumOrderByKeys; int /*<<< orphan*/  ioss_OrderByKeys; int /*<<< orphan*/  ioss_NumScanKeys; int /*<<< orphan*/  ioss_ScanKeys; scalar_t__ ioss_RuntimeKeysReady; TYPE_6__* ioss_ScanDesc; int /*<<< orphan*/  ioss_RelationDesc; TYPE_2__ ss; } ;
struct TYPE_31__ {int xs_want_itup; scalar_t__ numberOfOrderBys; int /*<<< orphan*/  heapRelation; scalar_t__ xs_recheckorderby; scalar_t__ xs_recheck; int /*<<< orphan*/  xs_itupdesc; scalar_t__ xs_itup; scalar_t__ xs_hitup; TYPE_4__* xs_hitupdesc; scalar_t__ xs_heap_continue; } ;
struct TYPE_29__ {scalar_t__ natts; } ;
struct TYPE_28__ {scalar_t__ natts; } ;
struct TYPE_25__ {int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_direction; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_6__* IndexScanDesc ;
typedef  TYPE_7__ IndexOnlyScanState ;
typedef  TYPE_8__ IndexOnlyScan ;
typedef  TYPE_9__ ExprContext ;
typedef  TYPE_10__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BackwardScanDirection ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_5__* ExecClearTuple (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (scalar_t__,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  InstrCountFiltered2 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  InstrCountTuples2 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StoreIndexTuple (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ALL_VISIBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_6__* index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_fetch_heap (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * index_getnext_tid (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
IndexOnlyNext(IndexOnlyScanState *node)
{
	EState	   *estate;
	ExprContext *econtext;
	ScanDirection direction;
	IndexScanDesc scandesc;
	TupleTableSlot *slot;
	ItemPointer tid;

	/*
	 * extract necessary information from index scan node
	 */
	estate = node->ss.ps.state;
	direction = estate->es_direction;
	/* flip direction if this is an overall backward scan */
	if (ScanDirectionIsBackward(((IndexOnlyScan *) node->ss.ps.plan)->indexorderdir))
	{
		if (ScanDirectionIsForward(direction))
			direction = BackwardScanDirection;
		else if (ScanDirectionIsBackward(direction))
			direction = ForwardScanDirection;
	}
	scandesc = node->ioss_ScanDesc;
	econtext = node->ss.ps.ps_ExprContext;
	slot = node->ss.ss_ScanTupleSlot;

	if (scandesc == NULL)
	{
		/*
		 * We reach here if the index only scan is not parallel, or if we're
		 * serially executing an index only scan that was planned to be
		 * parallel.
		 */
		scandesc = index_beginscan(node->ss.ss_currentRelation,
								   node->ioss_RelationDesc,
								   estate->es_snapshot,
								   node->ioss_NumScanKeys,
								   node->ioss_NumOrderByKeys);

		node->ioss_ScanDesc = scandesc;


		/* Set it up for index-only scan */
		node->ioss_ScanDesc->xs_want_itup = true;
		node->ioss_VMBuffer = InvalidBuffer;

		/*
		 * If no run-time keys to calculate or they are ready, go ahead and
		 * pass the scankeys to the index AM.
		 */
		if (node->ioss_NumRuntimeKeys == 0 || node->ioss_RuntimeKeysReady)
			index_rescan(scandesc,
						 node->ioss_ScanKeys,
						 node->ioss_NumScanKeys,
						 node->ioss_OrderByKeys,
						 node->ioss_NumOrderByKeys);
	}

	/*
	 * OK, now that we have what we need, fetch the next tuple.
	 */
	while ((tid = index_getnext_tid(scandesc, direction)) != NULL)
	{
		bool		tuple_from_heap = false;

		CHECK_FOR_INTERRUPTS();

		/*
		 * We can skip the heap fetch if the TID references a heap page on
		 * which all tuples are known visible to everybody.  In any case,
		 * we'll use the index tuple not the heap tuple as the data source.
		 *
		 * Note on Memory Ordering Effects: visibilitymap_get_status does not
		 * lock the visibility map buffer, and therefore the result we read
		 * here could be slightly stale.  However, it can't be stale enough to
		 * matter.
		 *
		 * We need to detect clearing a VM bit due to an insert right away,
		 * because the tuple is present in the index page but not visible. The
		 * reading of the TID by this scan (using a shared lock on the index
		 * buffer) is serialized with the insert of the TID into the index
		 * (using an exclusive lock on the index buffer). Because the VM bit
		 * is cleared before updating the index, and locking/unlocking of the
		 * index page acts as a full memory barrier, we are sure to see the
		 * cleared bit if we see a recently-inserted TID.
		 *
		 * Deletes do not update the index page (only VACUUM will clear out
		 * the TID), so the clearing of the VM bit by a delete is not
		 * serialized with this test below, and we may see a value that is
		 * significantly stale. However, we don't care about the delete right
		 * away, because the tuple is still visible until the deleting
		 * transaction commits or the statement ends (if it's our
		 * transaction). In either case, the lock on the VM buffer will have
		 * been released (acting as a write barrier) after clearing the bit.
		 * And for us to have a snapshot that includes the deleting
		 * transaction (making the tuple invisible), we must have acquired
		 * ProcArrayLock after that time, acting as a read barrier.
		 *
		 * It's worth going through this complexity to avoid needing to lock
		 * the VM buffer, which could cause significant contention.
		 */
		if (!VM_ALL_VISIBLE(scandesc->heapRelation,
							ItemPointerGetBlockNumber(tid),
							&node->ioss_VMBuffer))
		{
			/*
			 * Rats, we have to visit the heap to check visibility.
			 */
			InstrCountTuples2(node, 1);
			if (!index_fetch_heap(scandesc, node->ioss_TableSlot))
				continue;		/* no visible tuple, try next index entry */

			ExecClearTuple(node->ioss_TableSlot);

			/*
			 * Only MVCC snapshots are supported here, so there should be no
			 * need to keep following the HOT chain once a visible entry has
			 * been found.  If we did want to allow that, we'd need to keep
			 * more state to remember not to call index_getnext_tid next time.
			 */
			if (scandesc->xs_heap_continue)
				elog(ERROR, "non-MVCC snapshots are not supported in index-only scans");

			/*
			 * Note: at this point we are holding a pin on the heap page, as
			 * recorded in scandesc->xs_cbuf.  We could release that pin now,
			 * but it's not clear whether it's a win to do so.  The next index
			 * entry might require a visit to the same heap page.
			 */

			tuple_from_heap = true;
		}

		/*
		 * Fill the scan tuple slot with data from the index.  This might be
		 * provided in either HeapTuple or IndexTuple format.  Conceivably an
		 * index AM might fill both fields, in which case we prefer the heap
		 * format, since it's probably a bit cheaper to fill a slot from.
		 */
		if (scandesc->xs_hitup)
		{
			/*
			 * We don't take the trouble to verify that the provided tuple has
			 * exactly the slot's format, but it seems worth doing a quick
			 * check on the number of fields.
			 */
			Assert(slot->tts_tupleDescriptor->natts ==
				   scandesc->xs_hitupdesc->natts);
			ExecForceStoreHeapTuple(scandesc->xs_hitup, slot, false);
		}
		else if (scandesc->xs_itup)
			StoreIndexTuple(slot, scandesc->xs_itup, scandesc->xs_itupdesc);
		else
			elog(ERROR, "no data returned for index-only scan");

		/*
		 * If the index was lossy, we have to recheck the index quals.
		 * (Currently, this can never happen, but we should support the case
		 * for possible future use, eg with GiST indexes.)
		 */
		if (scandesc->xs_recheck)
		{
			econtext->ecxt_scantuple = slot;
			if (!ExecQualAndReset(node->indexqual, econtext))
			{
				/* Fails recheck, so drop it and loop back for another */
				InstrCountFiltered2(node, 1);
				continue;
			}
		}

		/*
		 * We don't currently support rechecking ORDER BY distances.  (In
		 * principle, if the index can support retrieval of the originally
		 * indexed value, it should be able to produce an exact distance
		 * calculation too.  So it's not clear that adding code here for
		 * recheck/re-sort would be worth the trouble.  But we should at least
		 * throw an error if someone tries it.)
		 */
		if (scandesc->numberOfOrderBys > 0 && scandesc->xs_recheckorderby)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("lossy distance functions are not supported in index-only scans")));

		/*
		 * If we didn't access the heap, then we'll need to take a predicate
		 * lock explicitly, as if we had.  For now we do that at page level.
		 */
		if (!tuple_from_heap)
			PredicateLockPage(scandesc->heapRelation,
							  ItemPointerGetBlockNumber(tid),
							  estate->es_snapshot);

		return slot;
	}

	/*
	 * if we get here it means the index scan failed so we are at the end of
	 * the scan..
	 */
	return ExecClearTuple(slot);
}