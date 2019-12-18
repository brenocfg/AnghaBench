#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ level; scalar_t__ firstright; scalar_t__ newitemoff; } ;
typedef  TYPE_2__ xl_btree_split ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_15__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_3__ XLogReaderState ;
struct TYPE_13__ {scalar_t__ level; } ;
struct TYPE_16__ {scalar_t__ btpo_prev; scalar_t__ btpo_cycleid; scalar_t__ btpo_next; int /*<<< orphan*/  btpo_flags; TYPE_1__ btpo; } ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_4__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BTP_INCOMPLETE_SPLIT ; 
 int /*<<< orphan*/  BTP_LEAF ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_4__*) ; 
 scalar_t__ P_HIKEY ; 
 scalar_t__ P_NONE ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 scalar_t__ PageGetTempPageCopySpecial (scalar_t__) ; 
 int /*<<< orphan*/  PageRestoreTempPage (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_3__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_3__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ XLogRecGetData (TYPE_3__*) ; 
 int /*<<< orphan*/  _bt_clear_incomplete_split (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _bt_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_restore_page (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
btree_xlog_split(bool onleft, XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_btree_split *xlrec = (xl_btree_split *) XLogRecGetData(record);
	bool		isleaf = (xlrec->level == 0);
	Buffer		lbuf;
	Buffer		rbuf;
	Page		rpage;
	BTPageOpaque ropaque;
	char	   *datapos;
	Size		datalen;
	BlockNumber leftsib;
	BlockNumber rightsib;
	BlockNumber rnext;

	XLogRecGetBlockTag(record, 0, NULL, NULL, &leftsib);
	XLogRecGetBlockTag(record, 1, NULL, NULL, &rightsib);
	if (!XLogRecGetBlockTag(record, 2, NULL, NULL, &rnext))
		rnext = P_NONE;

	/*
	 * Clear the incomplete split flag on the left sibling of the child page
	 * this is a downlink for.  (Like in btree_xlog_insert, this can be done
	 * before locking the other pages)
	 */
	if (!isleaf)
		_bt_clear_incomplete_split(record, 3);

	/* Reconstruct right (new) sibling page from scratch */
	rbuf = XLogInitBufferForRedo(record, 1);
	datapos = XLogRecGetBlockData(record, 1, &datalen);
	rpage = (Page) BufferGetPage(rbuf);

	_bt_pageinit(rpage, BufferGetPageSize(rbuf));
	ropaque = (BTPageOpaque) PageGetSpecialPointer(rpage);

	ropaque->btpo_prev = leftsib;
	ropaque->btpo_next = rnext;
	ropaque->btpo.level = xlrec->level;
	ropaque->btpo_flags = isleaf ? BTP_LEAF : 0;
	ropaque->btpo_cycleid = 0;

	_bt_restore_page(rpage, datapos, datalen);

	PageSetLSN(rpage, lsn);
	MarkBufferDirty(rbuf);

	/* Now reconstruct left (original) sibling page */
	if (XLogReadBufferForRedo(record, 0, &lbuf) == BLK_NEEDS_REDO)
	{
		/*
		 * To retain the same physical order of the tuples that they had, we
		 * initialize a temporary empty page for the left page and add all the
		 * items to that in item number order.  This mirrors how _bt_split()
		 * works.  Retaining the same physical order makes WAL consistency
		 * checking possible.  See also _bt_restore_page(), which does the
		 * same for the right page.
		 */
		Page		lpage = (Page) BufferGetPage(lbuf);
		BTPageOpaque lopaque = (BTPageOpaque) PageGetSpecialPointer(lpage);
		OffsetNumber off;
		IndexTuple	newitem = NULL,
					left_hikey = NULL;
		Size		newitemsz = 0,
					left_hikeysz = 0;
		Page		newlpage;
		OffsetNumber leftoff;

		datapos = XLogRecGetBlockData(record, 0, &datalen);

		if (onleft)
		{
			newitem = (IndexTuple) datapos;
			newitemsz = MAXALIGN(IndexTupleSize(newitem));
			datapos += newitemsz;
			datalen -= newitemsz;
		}

		/* Extract left hikey and its size (assuming 16-bit alignment) */
		left_hikey = (IndexTuple) datapos;
		left_hikeysz = MAXALIGN(IndexTupleSize(left_hikey));
		datapos += left_hikeysz;
		datalen -= left_hikeysz;

		Assert(datalen == 0);

		newlpage = PageGetTempPageCopySpecial(lpage);

		/* Set high key */
		leftoff = P_HIKEY;
		if (PageAddItem(newlpage, (Item) left_hikey, left_hikeysz,
						P_HIKEY, false, false) == InvalidOffsetNumber)
			elog(PANIC, "failed to add high key to left page after split");
		leftoff = OffsetNumberNext(leftoff);

		for (off = P_FIRSTDATAKEY(lopaque); off < xlrec->firstright; off++)
		{
			ItemId		itemid;
			Size		itemsz;
			IndexTuple	item;

			/* add the new item if it was inserted on left page */
			if (onleft && off == xlrec->newitemoff)
			{
				if (PageAddItem(newlpage, (Item) newitem, newitemsz, leftoff,
								false, false) == InvalidOffsetNumber)
					elog(ERROR, "failed to add new item to left page after split");
				leftoff = OffsetNumberNext(leftoff);
			}

			itemid = PageGetItemId(lpage, off);
			itemsz = ItemIdGetLength(itemid);
			item = (IndexTuple) PageGetItem(lpage, itemid);
			if (PageAddItem(newlpage, (Item) item, itemsz, leftoff,
							false, false) == InvalidOffsetNumber)
				elog(ERROR, "failed to add old item to left page after split");
			leftoff = OffsetNumberNext(leftoff);
		}

		/* cope with possibility that newitem goes at the end */
		if (onleft && off == xlrec->newitemoff)
		{
			if (PageAddItem(newlpage, (Item) newitem, newitemsz, leftoff,
							false, false) == InvalidOffsetNumber)
				elog(ERROR, "failed to add new item to left page after split");
			leftoff = OffsetNumberNext(leftoff);
		}

		PageRestoreTempPage(newlpage, lpage);

		/* Fix opaque fields */
		lopaque->btpo_flags = BTP_INCOMPLETE_SPLIT;
		if (isleaf)
			lopaque->btpo_flags |= BTP_LEAF;
		lopaque->btpo_next = rightsib;
		lopaque->btpo_cycleid = 0;

		PageSetLSN(lpage, lsn);
		MarkBufferDirty(lbuf);
	}

	/*
	 * We no longer need the buffers.  They must be released together, so that
	 * readers cannot observe two inconsistent halves.
	 */
	if (BufferIsValid(lbuf))
		UnlockReleaseBuffer(lbuf);
	UnlockReleaseBuffer(rbuf);

	/*
	 * Fix left-link of the page to the right of the new right sibling.
	 *
	 * Note: in normal operation, we do this while still holding lock on the
	 * two split pages.  However, that's not necessary for correctness in WAL
	 * replay, because no other index update can be in progress, and readers
	 * will cope properly when following an obsolete left-link.
	 */
	if (rnext != P_NONE)
	{
		Buffer		buffer;

		if (XLogReadBufferForRedo(record, 2, &buffer) == BLK_NEEDS_REDO)
		{
			Page		page = (Page) BufferGetPage(buffer);
			BTPageOpaque pageop = (BTPageOpaque) PageGetSpecialPointer(page);

			pageop->btpo_prev = rightsib;

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}
}