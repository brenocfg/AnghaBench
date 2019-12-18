#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ buf; int firstItem; int lastItem; TYPE_3__* items; int /*<<< orphan*/  currPage; } ;
struct TYPE_13__ {int /*<<< orphan*/  hasho_flag; } ;
struct TYPE_12__ {int numKilled; int* killedItems; scalar_t__ hashso_bucket_buf; TYPE_7__ currPos; } ;
struct TYPE_11__ {int /*<<< orphan*/  heapTid; int /*<<< orphan*/  indexOffset; } ;
struct TYPE_10__ {int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__ HashScanPosItem ;
typedef  TYPE_4__* HashScanOpaque ;
typedef  TYPE_5__* HashPageOpaque ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  HASH_READ ; 
 scalar_t__ HashScanPosIsPinned (TYPE_7__) ; 
 int HashScanPosIsValid (TYPE_7__) ; 
 int /*<<< orphan*/  ItemIdMarkDead (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  LH_PAGE_HAS_DEAD_TUPLES ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (scalar_t__,int) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 

void
_hash_kill_items(IndexScanDesc scan)
{
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	Relation	rel = scan->indexRelation;
	BlockNumber blkno;
	Buffer		buf;
	Page		page;
	HashPageOpaque opaque;
	OffsetNumber offnum,
				maxoff;
	int			numKilled = so->numKilled;
	int			i;
	bool		killedsomething = false;
	bool		havePin = false;

	Assert(so->numKilled > 0);
	Assert(so->killedItems != NULL);
	Assert(HashScanPosIsValid(so->currPos));

	/*
	 * Always reset the scan state, so we don't look for same items on other
	 * pages.
	 */
	so->numKilled = 0;

	blkno = so->currPos.currPage;
	if (HashScanPosIsPinned(so->currPos))
	{
		/*
		 * We already have pin on this buffer, so, all we need to do is
		 * acquire lock on it.
		 */
		havePin = true;
		buf = so->currPos.buf;
		LockBuffer(buf, BUFFER_LOCK_SHARE);
	}
	else
		buf = _hash_getbuf(rel, blkno, HASH_READ, LH_OVERFLOW_PAGE);

	page = BufferGetPage(buf);
	opaque = (HashPageOpaque) PageGetSpecialPointer(page);
	maxoff = PageGetMaxOffsetNumber(page);

	for (i = 0; i < numKilled; i++)
	{
		int			itemIndex = so->killedItems[i];
		HashScanPosItem *currItem = &so->currPos.items[itemIndex];

		offnum = currItem->indexOffset;

		Assert(itemIndex >= so->currPos.firstItem &&
			   itemIndex <= so->currPos.lastItem);

		while (offnum <= maxoff)
		{
			ItemId		iid = PageGetItemId(page, offnum);
			IndexTuple	ituple = (IndexTuple) PageGetItem(page, iid);

			if (ItemPointerEquals(&ituple->t_tid, &currItem->heapTid))
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
	 * Since this can be redone later if needed, mark as dirty hint. Whenever
	 * we mark anything LP_DEAD, we also set the page's
	 * LH_PAGE_HAS_DEAD_TUPLES flag, which is likewise just a hint.
	 */
	if (killedsomething)
	{
		opaque->hasho_flag |= LH_PAGE_HAS_DEAD_TUPLES;
		MarkBufferDirtyHint(buf, true);
	}

	if (so->hashso_bucket_buf == so->currPos.buf ||
		havePin)
		LockBuffer(so->currPos.buf, BUFFER_LOCK_UNLOCK);
	else
		_hash_relbuf(rel, buf);
}