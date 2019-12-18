#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t itemIndex; TYPE_2__* items; int /*<<< orphan*/  buf; } ;
struct TYPE_13__ {scalar_t__ currTuples; TYPE_9__ currPos; } ;
struct TYPE_12__ {scalar_t__ tupleOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_11__ {scalar_t__ xs_itup; scalar_t__ xs_want_itup; int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  opaque; int /*<<< orphan*/  indexRelation; } ;
typedef  scalar_t__ ScanDirection ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_2__ BTScanPosItem ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  scalar_t__ BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTScanPosInvalidate (TYPE_9__) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_FIRSTDATAKEY (scalar_t__) ; 
 int /*<<< orphan*/  P_ISLEAF (scalar_t__) ; 
 int /*<<< orphan*/  P_RIGHTMOST (scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockRelation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsBackward (scalar_t__) ; 
 scalar_t__ ScanDirectionIsForward (scalar_t__) ; 
 int /*<<< orphan*/  _bt_drop_lock_and_maybe_pin (TYPE_1__*,TYPE_9__*) ; 
 int /*<<< orphan*/  _bt_get_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_initialize_more_data (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  _bt_readpage (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _bt_steppage (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
_bt_endpoint(IndexScanDesc scan, ScanDirection dir)
{
	Relation	rel = scan->indexRelation;
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Buffer		buf;
	Page		page;
	BTPageOpaque opaque;
	OffsetNumber start;
	BTScanPosItem *currItem;

	/*
	 * Scan down to the leftmost or rightmost leaf page.  This is a simplified
	 * version of _bt_search().  We don't maintain a stack since we know we
	 * won't need it.
	 */
	buf = _bt_get_endpoint(rel, 0, ScanDirectionIsBackward(dir), scan->xs_snapshot);

	if (!BufferIsValid(buf))
	{
		/*
		 * Empty index. Lock the whole relation, as nothing finer to lock
		 * exists.
		 */
		PredicateLockRelation(rel, scan->xs_snapshot);
		BTScanPosInvalidate(so->currPos);
		return false;
	}

	PredicateLockPage(rel, BufferGetBlockNumber(buf), scan->xs_snapshot);
	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	Assert(P_ISLEAF(opaque));

	if (ScanDirectionIsForward(dir))
	{
		/* There could be dead pages to the left, so not this: */
		/* Assert(P_LEFTMOST(opaque)); */

		start = P_FIRSTDATAKEY(opaque);
	}
	else if (ScanDirectionIsBackward(dir))
	{
		Assert(P_RIGHTMOST(opaque));

		start = PageGetMaxOffsetNumber(page);
	}
	else
	{
		elog(ERROR, "invalid scan direction: %d", (int) dir);
		start = 0;				/* keep compiler quiet */
	}

	/* remember which buffer we have pinned */
	so->currPos.buf = buf;

	_bt_initialize_more_data(so, dir);

	/*
	 * Now load data from the first page of the scan.
	 */
	if (!_bt_readpage(scan, dir, start))
	{
		/*
		 * There's no actually-matching data on this page.  Try to advance to
		 * the next page.  Return false if there's no matching data at all.
		 */
		LockBuffer(so->currPos.buf, BUFFER_LOCK_UNLOCK);
		if (!_bt_steppage(scan, dir))
			return false;
	}
	else
	{
		/* Drop the lock, and maybe the pin, on the current page */
		_bt_drop_lock_and_maybe_pin(scan, &so->currPos);
	}

	/* OK, itemIndex says what to return */
	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;
	if (scan->xs_want_itup)
		scan->xs_itup = (IndexTuple) (so->currTuples + currItem->tupleOffset);

	return true;
}