#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_10__ {int rs_flags; int /*<<< orphan*/  rs_rd; TYPE_2__* rs_snapshot; } ;
struct TYPE_13__ {scalar_t__ rs_nblocks; int* rs_vistuples; int rs_ntuples; TYPE_1__ rs_base; int /*<<< orphan*/  rs_cbuf; scalar_t__ rs_cblock; int /*<<< orphan*/  rs_strategy; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; scalar_t__ t_data; int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_11__ {int /*<<< orphan*/  takenDuringRecovery; } ;
typedef  TYPE_2__* Snapshot ;
typedef  scalar_t__ Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_3__ HeapTupleData ;
typedef  TYPE_4__* HeapScanDesc ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CheckForSerializableConflictOut (int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int FirstOffsetNumber ; 
 int HeapTupleSatisfiesVisibility (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int MaxHeapTuplesPerPage ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int) ; 
 int PageGetMaxOffsetNumber (scalar_t__) ; 
 scalar_t__ PageIsAllVisible (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int SO_ALLOW_PAGEMODE ; 
 int /*<<< orphan*/  TestForOldSnapshot (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  heap_page_prune_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
heapgetpage(TableScanDesc sscan, BlockNumber page)
{
	HeapScanDesc scan = (HeapScanDesc) sscan;
	Buffer		buffer;
	Snapshot	snapshot;
	Page		dp;
	int			lines;
	int			ntup;
	OffsetNumber lineoff;
	ItemId		lpp;
	bool		all_visible;

	Assert(page < scan->rs_nblocks);

	/* release previous scan buffer, if any */
	if (BufferIsValid(scan->rs_cbuf))
	{
		ReleaseBuffer(scan->rs_cbuf);
		scan->rs_cbuf = InvalidBuffer;
	}

	/*
	 * Be sure to check for interrupts at least once per page.  Checks at
	 * higher code levels won't be able to stop a seqscan that encounters many
	 * pages' worth of consecutive dead tuples.
	 */
	CHECK_FOR_INTERRUPTS();

	/* read page using selected strategy */
	scan->rs_cbuf = ReadBufferExtended(scan->rs_base.rs_rd, MAIN_FORKNUM, page,
									   RBM_NORMAL, scan->rs_strategy);
	scan->rs_cblock = page;

	if (!(scan->rs_base.rs_flags & SO_ALLOW_PAGEMODE))
		return;

	buffer = scan->rs_cbuf;
	snapshot = scan->rs_base.rs_snapshot;

	/*
	 * Prune and repair fragmentation for the whole page, if possible.
	 */
	heap_page_prune_opt(scan->rs_base.rs_rd, buffer);

	/*
	 * We must hold share lock on the buffer content while examining tuple
	 * visibility.  Afterwards, however, the tuples we have found to be
	 * visible are guaranteed good as long as we hold the buffer pin.
	 */
	LockBuffer(buffer, BUFFER_LOCK_SHARE);

	dp = BufferGetPage(buffer);
	TestForOldSnapshot(snapshot, scan->rs_base.rs_rd, dp);
	lines = PageGetMaxOffsetNumber(dp);
	ntup = 0;

	/*
	 * If the all-visible flag indicates that all tuples on the page are
	 * visible to everyone, we can skip the per-tuple visibility tests.
	 *
	 * Note: In hot standby, a tuple that's already visible to all
	 * transactions in the master might still be invisible to a read-only
	 * transaction in the standby. We partly handle this problem by tracking
	 * the minimum xmin of visible tuples as the cut-off XID while marking a
	 * page all-visible on master and WAL log that along with the visibility
	 * map SET operation. In hot standby, we wait for (or abort) all
	 * transactions that can potentially may not see one or more tuples on the
	 * page. That's how index-only scans work fine in hot standby. A crucial
	 * difference between index-only scans and heap scans is that the
	 * index-only scan completely relies on the visibility map where as heap
	 * scan looks at the page-level PD_ALL_VISIBLE flag. We are not sure if
	 * the page-level flag can be trusted in the same way, because it might
	 * get propagated somehow without being explicitly WAL-logged, e.g. via a
	 * full page write. Until we can prove that beyond doubt, let's check each
	 * tuple for visibility the hard way.
	 */
	all_visible = PageIsAllVisible(dp) && !snapshot->takenDuringRecovery;

	for (lineoff = FirstOffsetNumber, lpp = PageGetItemId(dp, lineoff);
		 lineoff <= lines;
		 lineoff++, lpp++)
	{
		if (ItemIdIsNormal(lpp))
		{
			HeapTupleData loctup;
			bool		valid;

			loctup.t_tableOid = RelationGetRelid(scan->rs_base.rs_rd);
			loctup.t_data = (HeapTupleHeader) PageGetItem((Page) dp, lpp);
			loctup.t_len = ItemIdGetLength(lpp);
			ItemPointerSet(&(loctup.t_self), page, lineoff);

			if (all_visible)
				valid = true;
			else
				valid = HeapTupleSatisfiesVisibility(&loctup, snapshot, buffer);

			CheckForSerializableConflictOut(valid, scan->rs_base.rs_rd,
											&loctup, buffer, snapshot);

			if (valid)
				scan->rs_vistuples[ntup++] = lineoff;
		}
	}

	LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

	Assert(ntup <= MaxHeapTuplesPerPage);
	scan->rs_ntuples = ntup;
}