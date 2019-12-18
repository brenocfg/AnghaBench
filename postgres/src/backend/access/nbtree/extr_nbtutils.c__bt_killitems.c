#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ lsn; int firstItem; int lastItem; int /*<<< orphan*/  buf; TYPE_3__* items; int /*<<< orphan*/  currPage; } ;
struct TYPE_14__ {int /*<<< orphan*/  btpo_flags; } ;
struct TYPE_13__ {int numKilled; int* killedItems; TYPE_8__ currPos; } ;
struct TYPE_12__ {scalar_t__ indexOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_11__ {int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_3__ BTScanPosItem ;
typedef  TYPE_4__* BTScanOpaque ;
typedef  TYPE_5__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 scalar_t__ BTScanPosIsPinned (TYPE_8__) ; 
 int BTScanPosIsValid (TYPE_8__) ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetLSNAtomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdMarkDead (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_5__*) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_bt_killitems(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Page		page;
	BTPageOpaque opaque;
	OffsetNumber minoff;
	OffsetNumber maxoff;
	int			i;
	int			numKilled = so->numKilled;
	bool		killedsomething = false;

	Assert(BTScanPosIsValid(so->currPos));

	/*
	 * Always reset the scan state, so we don't look for same items on other
	 * pages.
	 */
	so->numKilled = 0;

	if (BTScanPosIsPinned(so->currPos))
	{
		/*
		 * We have held the pin on this page since we read the index tuples,
		 * so all we need to do is lock it.  The pin will have prevented
		 * re-use of any TID on the page, so there is no need to check the
		 * LSN.
		 */
		LockBuffer(so->currPos.buf, BT_READ);

		page = BufferGetPage(so->currPos.buf);
	}
	else
	{
		Buffer		buf;

		/* Attempt to re-read the buffer, getting pin and lock. */
		buf = _bt_getbuf(scan->indexRelation, so->currPos.currPage, BT_READ);

		/* It might not exist anymore; in which case we can't hint it. */
		if (!BufferIsValid(buf))
			return;

		page = BufferGetPage(buf);
		if (BufferGetLSNAtomic(buf) == so->currPos.lsn)
			so->currPos.buf = buf;
		else
		{
			/* Modified while not pinned means hinting is not safe. */
			_bt_relbuf(scan->indexRelation, buf);
			return;
		}
	}

	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	minoff = P_FIRSTDATAKEY(opaque);
	maxoff = PageGetMaxOffsetNumber(page);

	for (i = 0; i < numKilled; i++)
	{
		int			itemIndex = so->killedItems[i];
		BTScanPosItem *kitem = &so->currPos.items[itemIndex];
		OffsetNumber offnum = kitem->indexOffset;

		Assert(itemIndex >= so->currPos.firstItem &&
			   itemIndex <= so->currPos.lastItem);
		if (offnum < minoff)
			continue;			/* pure paranoia */
		while (offnum <= maxoff)
		{
			ItemId		iid = PageGetItemId(page, offnum);
			IndexTuple	ituple = (IndexTuple) PageGetItem(page, iid);

			if (ItemPointerEquals(&ituple->t_tid, &kitem->heapTid))
			{
				/* found the item */
				ItemIdMarkDead(iid);
				killedsomething = true;
				break;			/* out of inner search loop */
			}
			offnum = OffsetNumberNext(offnum);
		}
	}

	/*
	 * Since this can be redone later if needed, mark as dirty hint.
	 *
	 * Whenever we mark anything LP_DEAD, we also set the page's
	 * BTP_HAS_GARBAGE flag, which is likewise just a hint.
	 */
	if (killedsomething)
	{
		opaque->btpo_flags |= BTP_HAS_GARBAGE;
		MarkBufferDirtyHint(so->currPos.buf, true);
	}

	LockBuffer(so->currPos.buf, BUFFER_LOCK_UNLOCK);
}