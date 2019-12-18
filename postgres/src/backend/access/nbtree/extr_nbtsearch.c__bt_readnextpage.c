#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ btpo_next; } ;
struct TYPE_14__ {scalar_t__ buf; scalar_t__ currPage; int /*<<< orphan*/  moreLeft; int /*<<< orphan*/  moreRight; } ;
struct TYPE_16__ {TYPE_11__ currPos; } ;
struct TYPE_15__ {int /*<<< orphan*/ * parallel_scan; int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__* BTScanOpaque ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BTScanPosInvalidate (TYPE_11__) ; 
 scalar_t__ BTScanPosIsPinned (TYPE_11__) ; 
 int /*<<< orphan*/  BTScanPosUnpinIfPinned (TYPE_11__) ; 
 int /*<<< orphan*/  BT_READ ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_FIRSTDATAKEY (TYPE_3__*) ; 
 int /*<<< orphan*/  P_IGNORE (TYPE_3__*) ; 
 scalar_t__ P_NONE ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _bt_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_parallel_done (TYPE_1__*) ; 
 int /*<<< orphan*/  _bt_parallel_release (TYPE_1__*,scalar_t__) ; 
 int _bt_parallel_seize (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ _bt_readpage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _bt_walk_left (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_bt_readnextpage(IndexScanDesc scan, BlockNumber blkno, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Relation	rel;
	Page		page;
	BTPageOpaque opaque;
	bool		status = true;

	rel = scan->indexRelation;

	if (ScanDirectionIsForward(dir))
	{
		for (;;)
		{
			/*
			 * if we're at end of scan, give up and mark parallel scan as
			 * done, so that all the workers can finish their scan
			 */
			if (blkno == P_NONE || !so->currPos.moreRight)
			{
				_bt_parallel_done(scan);
				BTScanPosInvalidate(so->currPos);
				return false;
			}
			/* check for interrupts while we're not holding any buffer lock */
			CHECK_FOR_INTERRUPTS();
			/* step right one page */
			so->currPos.buf = _bt_getbuf(rel, blkno, BT_READ);
			page = BufferGetPage(so->currPos.buf);
			TestForOldSnapshot(scan->xs_snapshot, rel, page);
			opaque = (BTPageOpaque) PageGetSpecialPointer(page);
			/* check for deleted page */
			if (!P_IGNORE(opaque))
			{
				PredicateLockPage(rel, blkno, scan->xs_snapshot);
				/* see if there are any matches on this page */
				/* note that this will clear moreRight if we can stop */
				if (_bt_readpage(scan, dir, P_FIRSTDATAKEY(opaque)))
					break;
			}
			else if (scan->parallel_scan != NULL)
			{
				/* allow next page be processed by parallel worker */
				_bt_parallel_release(scan, opaque->btpo_next);
			}

			/* nope, keep going */
			if (scan->parallel_scan != NULL)
			{
				_bt_relbuf(rel, so->currPos.buf);
				status = _bt_parallel_seize(scan, &blkno);
				if (!status)
				{
					BTScanPosInvalidate(so->currPos);
					return false;
				}
			}
			else
			{
				blkno = opaque->btpo_next;
				_bt_relbuf(rel, so->currPos.buf);
			}
		}
	}
	else
	{
		/*
		 * Should only happen in parallel cases, when some other backend
		 * advanced the scan.
		 */
		if (so->currPos.currPage != blkno)
		{
			BTScanPosUnpinIfPinned(so->currPos);
			so->currPos.currPage = blkno;
		}

		/*
		 * Walk left to the next page with data.  This is much more complex
		 * than the walk-right case because of the possibility that the page
		 * to our left splits while we are in flight to it, plus the
		 * possibility that the page we were on gets deleted after we leave
		 * it.  See nbtree/README for details.
		 *
		 * It might be possible to rearrange this code to have less overhead
		 * in pinning and locking, but that would require capturing the left
		 * pointer when the page is initially read, and using it here, along
		 * with big changes to _bt_walk_left() and the code below.  It is not
		 * clear whether this would be a win, since if the page immediately to
		 * the left splits after we read this page and before we step left, we
		 * would need to visit more pages than with the current code.
		 *
		 * Note that if we change the code so that we drop the pin for a scan
		 * which uses a non-MVCC snapshot, we will need to modify the code for
		 * walking left, to allow for the possibility that a referenced page
		 * has been deleted.  As long as the buffer is pinned or the snapshot
		 * is MVCC the page cannot move past the half-dead state to fully
		 * deleted.
		 */
		if (BTScanPosIsPinned(so->currPos))
			LockBuffer(so->currPos.buf, BT_READ);
		else
			so->currPos.buf = _bt_getbuf(rel, so->currPos.currPage, BT_READ);

		for (;;)
		{
			/* Done if we know there are no matching keys to the left */
			if (!so->currPos.moreLeft)
			{
				_bt_relbuf(rel, so->currPos.buf);
				_bt_parallel_done(scan);
				BTScanPosInvalidate(so->currPos);
				return false;
			}

			/* Step to next physical page */
			so->currPos.buf = _bt_walk_left(rel, so->currPos.buf,
											scan->xs_snapshot);

			/* if we're physically at end of index, return failure */
			if (so->currPos.buf == InvalidBuffer)
			{
				_bt_parallel_done(scan);
				BTScanPosInvalidate(so->currPos);
				return false;
			}

			/*
			 * Okay, we managed to move left to a non-deleted page. Done if
			 * it's not half-dead and contains matching tuples. Else loop back
			 * and do it all again.
			 */
			page = BufferGetPage(so->currPos.buf);
			TestForOldSnapshot(scan->xs_snapshot, rel, page);
			opaque = (BTPageOpaque) PageGetSpecialPointer(page);
			if (!P_IGNORE(opaque))
			{
				PredicateLockPage(rel, BufferGetBlockNumber(so->currPos.buf), scan->xs_snapshot);
				/* see if there are any matches on this page */
				/* note that this will clear moreLeft if we can stop */
				if (_bt_readpage(scan, dir, PageGetMaxOffsetNumber(page)))
					break;
			}
			else if (scan->parallel_scan != NULL)
			{
				/* allow next page be processed by parallel worker */
				_bt_parallel_release(scan, BufferGetBlockNumber(so->currPos.buf));
			}

			/*
			 * For parallel scans, get the last page scanned as it is quite
			 * possible that by the time we try to seize the scan, some other
			 * worker has already advanced the scan to a different page.  We
			 * must continue based on the latest page scanned by any worker.
			 */
			if (scan->parallel_scan != NULL)
			{
				_bt_relbuf(rel, so->currPos.buf);
				status = _bt_parallel_seize(scan, &blkno);
				if (!status)
				{
					BTScanPosInvalidate(so->currPos);
					return false;
				}
				so->currPos.buf = _bt_getbuf(rel, blkno, BT_READ);
			}
		}
	}

	return true;
}