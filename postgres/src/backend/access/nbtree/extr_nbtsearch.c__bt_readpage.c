#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  btpo_next; } ;
struct TYPE_11__ {int moreRight; int firstItem; int lastItem; int itemIndex; int moreLeft; scalar_t__ nextTupleOffset; int /*<<< orphan*/  nextPage; int /*<<< orphan*/  buf; int /*<<< orphan*/  lsn; int /*<<< orphan*/  currPage; } ;
struct TYPE_13__ {TYPE_10__ currPos; } ;
struct TYPE_12__ {scalar_t__ ignore_killed_tuples; int /*<<< orphan*/  indexRelation; scalar_t__ parallel_scan; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BTScanOpaque ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BTScanPosIsPinned (TYPE_10__) ; 
 int BTreeTupleGetNAtts (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetLSNAtomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int BufferIsValid (int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 scalar_t__ Max (scalar_t__,scalar_t__) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ Min (scalar_t__,scalar_t__) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ OffsetNumberPrev (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_3__*) ; 
 scalar_t__ P_HIKEY ; 
 int /*<<< orphan*/  P_RIGHTMOST (TYPE_3__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int _bt_checkkeys (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _bt_parallel_release (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_saveitem (TYPE_2__*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
_bt_readpage(IndexScanDesc scan, ScanDirection dir, OffsetNumber offnum)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Page		page;
	BTPageOpaque opaque;
	OffsetNumber minoff;
	OffsetNumber maxoff;
	int			itemIndex;
	bool		continuescan;
	int			indnatts;

	/*
	 * We must have the buffer pinned and locked, but the usual macro can't be
	 * used here; this function is what makes it good for currPos.
	 */
	Assert(BufferIsValid(so->currPos.buf));

	page = BufferGetPage(so->currPos.buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	/* allow next page be processed by parallel worker */
	if (scan->parallel_scan)
	{
		if (ScanDirectionIsForward(dir))
			_bt_parallel_release(scan, opaque->btpo_next);
		else
			_bt_parallel_release(scan, BufferGetBlockNumber(so->currPos.buf));
	}

	continuescan = true;		/* default assumption */
	indnatts = IndexRelationGetNumberOfAttributes(scan->indexRelation);
	minoff = P_FIRSTDATAKEY(opaque);
	maxoff = PageGetMaxOffsetNumber(page);

	/*
	 * We note the buffer's block number so that we can release the pin later.
	 * This allows us to re-read the buffer if it is needed again for hinting.
	 */
	so->currPos.currPage = BufferGetBlockNumber(so->currPos.buf);

	/*
	 * We save the LSN of the page as we read it, so that we know whether it
	 * safe to apply LP_DEAD hints to the page later.  This allows us to drop
	 * the pin for MVCC scans, which allows vacuum to avoid blocking.
	 */
	so->currPos.lsn = BufferGetLSNAtomic(so->currPos.buf);

	/*
	 * we must save the page's right-link while scanning it; this tells us
	 * where to step right to after we're done with these items.  There is no
	 * corresponding need for the left-link, since splits always go right.
	 */
	so->currPos.nextPage = opaque->btpo_next;

	/* initialize tuple workspace to empty */
	so->currPos.nextTupleOffset = 0;

	/*
	 * Now that the current page has been made consistent, the macro should be
	 * good.
	 */
	Assert(BTScanPosIsPinned(so->currPos));

	if (ScanDirectionIsForward(dir))
	{
		/* load items[] in ascending order */
		itemIndex = 0;

		offnum = Max(offnum, minoff);

		while (offnum <= maxoff)
		{
			ItemId		iid = PageGetItemId(page, offnum);
			IndexTuple	itup;

			/*
			 * If the scan specifies not to return killed tuples, then we
			 * treat a killed tuple as not passing the qual
			 */
			if (scan->ignore_killed_tuples && ItemIdIsDead(iid))
			{
				offnum = OffsetNumberNext(offnum);
				continue;
			}

			itup = (IndexTuple) PageGetItem(page, iid);

			if (_bt_checkkeys(scan, itup, indnatts, dir, &continuescan))
			{
				/* tuple passes all scan key conditions, so remember it */
				_bt_saveitem(so, itemIndex, offnum, itup);
				itemIndex++;
			}
			/* When !continuescan, there can't be any more matches, so stop */
			if (!continuescan)
				break;

			offnum = OffsetNumberNext(offnum);
		}

		/*
		 * We don't need to visit page to the right when the high key
		 * indicates that no more matches will be found there.
		 *
		 * Checking the high key like this works out more often than you might
		 * think.  Leaf page splits pick a split point between the two most
		 * dissimilar tuples (this is weighed against the need to evenly share
		 * free space).  Leaf pages with high key attribute values that can
		 * only appear on non-pivot tuples on the right sibling page are
		 * common.
		 */
		if (continuescan && !P_RIGHTMOST(opaque))
		{
			ItemId		iid = PageGetItemId(page, P_HIKEY);
			IndexTuple	itup = (IndexTuple) PageGetItem(page, iid);
			int			truncatt;

			truncatt = BTreeTupleGetNAtts(itup, scan->indexRelation);
			_bt_checkkeys(scan, itup, truncatt, dir, &continuescan);
		}

		if (!continuescan)
			so->currPos.moreRight = false;

		Assert(itemIndex <= MaxIndexTuplesPerPage);
		so->currPos.firstItem = 0;
		so->currPos.lastItem = itemIndex - 1;
		so->currPos.itemIndex = 0;
	}
	else
	{
		/* load items[] in descending order */
		itemIndex = MaxIndexTuplesPerPage;

		offnum = Min(offnum, maxoff);

		while (offnum >= minoff)
		{
			ItemId		iid = PageGetItemId(page, offnum);
			IndexTuple	itup;
			bool		tuple_alive;
			bool		passes_quals;

			/*
			 * If the scan specifies not to return killed tuples, then we
			 * treat a killed tuple as not passing the qual.  Most of the
			 * time, it's a win to not bother examining the tuple's index
			 * keys, but just skip to the next tuple (previous, actually,
			 * since we're scanning backwards).  However, if this is the first
			 * tuple on the page, we do check the index keys, to prevent
			 * uselessly advancing to the page to the left.  This is similar
			 * to the high key optimization used by forward scans.
			 */
			if (scan->ignore_killed_tuples && ItemIdIsDead(iid))
			{
				Assert(offnum >= P_FIRSTDATAKEY(opaque));
				if (offnum > P_FIRSTDATAKEY(opaque))
				{
					offnum = OffsetNumberPrev(offnum);
					continue;
				}

				tuple_alive = false;
			}
			else
				tuple_alive = true;

			itup = (IndexTuple) PageGetItem(page, iid);

			passes_quals = _bt_checkkeys(scan, itup, indnatts, dir,
										 &continuescan);
			if (passes_quals && tuple_alive)
			{
				/* tuple passes all scan key conditions, so remember it */
				itemIndex--;
				_bt_saveitem(so, itemIndex, offnum, itup);
			}
			if (!continuescan)
			{
				/* there can't be any more matches, so stop */
				so->currPos.moreLeft = false;
				break;
			}

			offnum = OffsetNumberPrev(offnum);
		}

		Assert(itemIndex >= 0);
		so->currPos.firstItem = itemIndex;
		so->currPos.lastItem = MaxIndexTuplesPerPage - 1;
		so->currPos.itemIndex = MaxIndexTuplesPerPage - 1;
	}

	return (so->currPos.firstItem <= so->currPos.lastItem);
}