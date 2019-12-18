#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ newitemoff; scalar_t__ firstright; int /*<<< orphan*/  level; } ;
typedef  TYPE_2__ xl_btree_split ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_11__ {int /*<<< orphan*/  level; } ;
struct TYPE_15__ {int btpo_flags; scalar_t__ btpo_prev; scalar_t__ btpo_cycleid; TYPE_1__ btpo; scalar_t__ btpo_next; } ;
struct TYPE_14__ {scalar_t__ heapkeyspace; } ;
struct TYPE_13__ {int pd_upper; int pd_special; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_3__* PageHeader ;
typedef  int /*<<< orphan*/ * Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_4__* BTScanInsert ;
typedef  TYPE_5__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BTP_HAS_GARBAGE ; 
 int BTP_INCOMPLETE_SPLIT ; 
 int BTP_ROOT ; 
 int BTP_SPLIT_END ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int BTreeTupleGetNAtts (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int IndexRelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ OffsetNumberPrev (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_5__*) ; 
 scalar_t__ P_HIKEY ; 
 int P_ISLEAF (TYPE_5__*) ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  P_RIGHTMOST (TYPE_5__*) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PageGetLSN (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetTempPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageRestoreTempPage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeSplit ; 
 int /*<<< orphan*/  XLOG_BTREE_SPLIT_L ; 
 int /*<<< orphan*/  XLOG_BTREE_SPLIT_R ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_findsplitloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_pageinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_pgaddtup (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_truncate (int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_4__*) ; 
 scalar_t__ _bt_vacuum_cycleid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static Buffer
_bt_split(Relation rel, BTScanInsert itup_key, Buffer buf, Buffer cbuf,
		  OffsetNumber newitemoff, Size newitemsz, IndexTuple newitem)
{
	Buffer		rbuf;
	Page		origpage;
	Page		leftpage,
				rightpage;
	BlockNumber origpagenumber,
				rightpagenumber;
	BTPageOpaque ropaque,
				lopaque,
				oopaque;
	Buffer		sbuf = InvalidBuffer;
	Page		spage = NULL;
	BTPageOpaque sopaque = NULL;
	Size		itemsz;
	ItemId		itemid;
	IndexTuple	item;
	OffsetNumber leftoff,
				rightoff;
	OffsetNumber firstright;
	OffsetNumber maxoff;
	OffsetNumber i;
	bool		newitemonleft,
				isleaf;
	IndexTuple	lefthikey;
	int			indnatts = IndexRelationGetNumberOfAttributes(rel);
	int			indnkeyatts = IndexRelationGetNumberOfKeyAttributes(rel);

	/*
	 * origpage is the original page to be split.  leftpage is a temporary
	 * buffer that receives the left-sibling data, which will be copied back
	 * into origpage on success.  rightpage is the new page that will receive
	 * the right-sibling data.
	 *
	 * leftpage is allocated after choosing a split point.  rightpage's new
	 * buffer isn't acquired until after leftpage is initialized and has new
	 * high key, the last point where splitting the page may fail (barring
	 * corruption).  Failing before acquiring new buffer won't have lasting
	 * consequences, since origpage won't have been modified and leftpage is
	 * only workspace.
	 */
	origpage = BufferGetPage(buf);
	oopaque = (BTPageOpaque) PageGetSpecialPointer(origpage);
	origpagenumber = BufferGetBlockNumber(buf);

	/*
	 * Choose a point to split origpage at.
	 *
	 * A split point can be thought of as a point _between_ two existing
	 * tuples on origpage (lastleft and firstright tuples), provided you
	 * pretend that the new item that didn't fit is already on origpage.
	 *
	 * Since origpage does not actually contain newitem, the representation of
	 * split points needs to work with two boundary cases: splits where
	 * newitem is lastleft, and splits where newitem is firstright.
	 * newitemonleft resolves the ambiguity that would otherwise exist when
	 * newitemoff == firstright.  In all other cases it's clear which side of
	 * the split every tuple goes on from context.  newitemonleft is usually
	 * (but not always) redundant information.
	 */
	firstright = _bt_findsplitloc(rel, origpage, newitemoff, newitemsz,
								  newitem, &newitemonleft);

	/* Allocate temp buffer for leftpage */
	leftpage = PageGetTempPage(origpage);
	_bt_pageinit(leftpage, BufferGetPageSize(buf));
	lopaque = (BTPageOpaque) PageGetSpecialPointer(leftpage);

	/*
	 * leftpage won't be the root when we're done.  Also, clear the SPLIT_END
	 * and HAS_GARBAGE flags.
	 */
	lopaque->btpo_flags = oopaque->btpo_flags;
	lopaque->btpo_flags &= ~(BTP_ROOT | BTP_SPLIT_END | BTP_HAS_GARBAGE);
	/* set flag in leftpage indicating that rightpage has no downlink yet */
	lopaque->btpo_flags |= BTP_INCOMPLETE_SPLIT;
	lopaque->btpo_prev = oopaque->btpo_prev;
	/* handle btpo_next after rightpage buffer acquired */
	lopaque->btpo.level = oopaque->btpo.level;
	/* handle btpo_cycleid after rightpage buffer acquired */

	/*
	 * Copy the original page's LSN into leftpage, which will become the
	 * updated version of the page.  We need this because XLogInsert will
	 * examine the LSN and possibly dump it in a page image.
	 */
	PageSetLSN(leftpage, PageGetLSN(origpage));
	isleaf = P_ISLEAF(oopaque);

	/*
	 * The "high key" for the new left page will be the first key that's going
	 * to go into the new right page, or a truncated version if this is a leaf
	 * page split.
	 *
	 * The high key for the left page is formed using the first item on the
	 * right page, which may seem to be contrary to Lehman & Yao's approach of
	 * using the left page's last item as its new high key when splitting on
	 * the leaf level.  It isn't, though: suffix truncation will leave the
	 * left page's high key fully equal to the last item on the left page when
	 * two tuples with equal key values (excluding heap TID) enclose the split
	 * point.  It isn't actually necessary for a new leaf high key to be equal
	 * to the last item on the left for the L&Y "subtree" invariant to hold.
	 * It's sufficient to make sure that the new leaf high key is strictly
	 * less than the first item on the right leaf page, and greater than or
	 * equal to (not necessarily equal to) the last item on the left leaf
	 * page.
	 *
	 * In other words, when suffix truncation isn't possible, L&Y's exact
	 * approach to leaf splits is taken.  (Actually, even that is slightly
	 * inaccurate.  A tuple with all the keys from firstright but the heap TID
	 * from lastleft will be used as the new high key, since the last left
	 * tuple could be physically larger despite being opclass-equal in respect
	 * of all attributes prior to the heap TID attribute.)
	 */
	if (!newitemonleft && newitemoff == firstright)
	{
		/* incoming tuple will become first on right page */
		itemsz = newitemsz;
		item = newitem;
	}
	else
	{
		/* existing item at firstright will become first on right page */
		itemid = PageGetItemId(origpage, firstright);
		itemsz = ItemIdGetLength(itemid);
		item = (IndexTuple) PageGetItem(origpage, itemid);
	}

	/*
	 * Truncate unneeded key and non-key attributes of the high key item
	 * before inserting it on the left page.  This can only happen at the leaf
	 * level, since in general all pivot tuple values originate from leaf
	 * level high keys.  A pivot tuple in a grandparent page must guide a
	 * search not only to the correct parent page, but also to the correct
	 * leaf page.
	 */
	if (isleaf && (itup_key->heapkeyspace || indnatts != indnkeyatts))
	{
		IndexTuple	lastleft;

		/*
		 * Determine which tuple will become the last on the left page.  This
		 * is needed to decide how many attributes from the first item on the
		 * right page must remain in new high key for left page.
		 */
		if (newitemonleft && newitemoff == firstright)
		{
			/* incoming tuple will become last on left page */
			lastleft = newitem;
		}
		else
		{
			OffsetNumber lastleftoff;

			/* item just before firstright will become last on left page */
			lastleftoff = OffsetNumberPrev(firstright);
			Assert(lastleftoff >= P_FIRSTDATAKEY(oopaque));
			itemid = PageGetItemId(origpage, lastleftoff);
			lastleft = (IndexTuple) PageGetItem(origpage, itemid);
		}

		Assert(lastleft != item);
		lefthikey = _bt_truncate(rel, lastleft, item, itup_key);
		itemsz = IndexTupleSize(lefthikey);
		itemsz = MAXALIGN(itemsz);
	}
	else
		lefthikey = item;

	/*
	 * Add new high key to leftpage
	 */
	leftoff = P_HIKEY;

	Assert(BTreeTupleGetNAtts(lefthikey, rel) > 0);
	Assert(BTreeTupleGetNAtts(lefthikey, rel) <= indnkeyatts);
	if (PageAddItem(leftpage, (Item) lefthikey, itemsz, leftoff,
					false, false) == InvalidOffsetNumber)
		elog(ERROR, "failed to add hikey to the left sibling"
			 " while splitting block %u of index \"%s\"",
			 origpagenumber, RelationGetRelationName(rel));
	leftoff = OffsetNumberNext(leftoff);
	/* be tidy */
	if (lefthikey != item)
		pfree(lefthikey);

	/*
	 * Acquire a new right page to split into, now that left page has a new
	 * high key.  From here on, it's not okay to throw an error without
	 * zeroing rightpage first.  This coding rule ensures that we won't
	 * confuse future VACUUM operations, which might otherwise try to re-find
	 * a downlink to a leftover junk page as the page undergoes deletion.
	 *
	 * It would be reasonable to start the critical section just after the new
	 * rightpage buffer is acquired instead; that would allow us to avoid
	 * leftover junk pages without bothering to zero rightpage.  We do it this
	 * way because it avoids an unnecessary PANIC when either origpage or its
	 * existing sibling page are corrupt.
	 */
	rbuf = _bt_getbuf(rel, P_NEW, BT_WRITE);
	rightpage = BufferGetPage(rbuf);
	rightpagenumber = BufferGetBlockNumber(rbuf);
	/* rightpage was initialized by _bt_getbuf */
	ropaque = (BTPageOpaque) PageGetSpecialPointer(rightpage);

	/*
	 * Finish off remaining leftpage special area fields.  They cannot be set
	 * before both origpage (leftpage) and rightpage buffers are acquired and
	 * locked.
	 */
	lopaque->btpo_next = rightpagenumber;
	lopaque->btpo_cycleid = _bt_vacuum_cycleid(rel);

	/*
	 * rightpage won't be the root when we're done.  Also, clear the SPLIT_END
	 * and HAS_GARBAGE flags.
	 */
	ropaque->btpo_flags = oopaque->btpo_flags;
	ropaque->btpo_flags &= ~(BTP_ROOT | BTP_SPLIT_END | BTP_HAS_GARBAGE);
	ropaque->btpo_prev = origpagenumber;
	ropaque->btpo_next = oopaque->btpo_next;
	ropaque->btpo.level = oopaque->btpo.level;
	ropaque->btpo_cycleid = lopaque->btpo_cycleid;

	/*
	 * Add new high key to rightpage where necessary.
	 *
	 * If the page we're splitting is not the rightmost page at its level in
	 * the tree, then the first entry on the page is the high key from
	 * origpage.
	 */
	rightoff = P_HIKEY;

	if (!P_RIGHTMOST(oopaque))
	{
		itemid = PageGetItemId(origpage, P_HIKEY);
		itemsz = ItemIdGetLength(itemid);
		item = (IndexTuple) PageGetItem(origpage, itemid);
		Assert(BTreeTupleGetNAtts(item, rel) > 0);
		Assert(BTreeTupleGetNAtts(item, rel) <= indnkeyatts);
		if (PageAddItem(rightpage, (Item) item, itemsz, rightoff,
						false, false) == InvalidOffsetNumber)
		{
			memset(rightpage, 0, BufferGetPageSize(rbuf));
			elog(ERROR, "failed to add hikey to the right sibling"
				 " while splitting block %u of index \"%s\"",
				 origpagenumber, RelationGetRelationName(rel));
		}
		rightoff = OffsetNumberNext(rightoff);
	}

	/*
	 * Now transfer all the data items (non-pivot tuples in isleaf case, or
	 * additional pivot tuples in !isleaf case) to the appropriate page.
	 *
	 * Note: we *must* insert at least the right page's items in item-number
	 * order, for the benefit of _bt_restore_page().
	 */
	maxoff = PageGetMaxOffsetNumber(origpage);

	for (i = P_FIRSTDATAKEY(oopaque); i <= maxoff; i = OffsetNumberNext(i))
	{
		itemid = PageGetItemId(origpage, i);
		itemsz = ItemIdGetLength(itemid);
		item = (IndexTuple) PageGetItem(origpage, itemid);

		/* does new item belong before this one? */
		if (i == newitemoff)
		{
			if (newitemonleft)
			{
				Assert(newitemoff <= firstright);
				if (!_bt_pgaddtup(leftpage, newitemsz, newitem, leftoff))
				{
					memset(rightpage, 0, BufferGetPageSize(rbuf));
					elog(ERROR, "failed to add new item to the left sibling"
						 " while splitting block %u of index \"%s\"",
						 origpagenumber, RelationGetRelationName(rel));
				}
				leftoff = OffsetNumberNext(leftoff);
			}
			else
			{
				Assert(newitemoff >= firstright);
				if (!_bt_pgaddtup(rightpage, newitemsz, newitem, rightoff))
				{
					memset(rightpage, 0, BufferGetPageSize(rbuf));
					elog(ERROR, "failed to add new item to the right sibling"
						 " while splitting block %u of index \"%s\"",
						 origpagenumber, RelationGetRelationName(rel));
				}
				rightoff = OffsetNumberNext(rightoff);
			}
		}

		/* decide which page to put it on */
		if (i < firstright)
		{
			if (!_bt_pgaddtup(leftpage, itemsz, item, leftoff))
			{
				memset(rightpage, 0, BufferGetPageSize(rbuf));
				elog(ERROR, "failed to add old item to the left sibling"
					 " while splitting block %u of index \"%s\"",
					 origpagenumber, RelationGetRelationName(rel));
			}
			leftoff = OffsetNumberNext(leftoff);
		}
		else
		{
			if (!_bt_pgaddtup(rightpage, itemsz, item, rightoff))
			{
				memset(rightpage, 0, BufferGetPageSize(rbuf));
				elog(ERROR, "failed to add old item to the right sibling"
					 " while splitting block %u of index \"%s\"",
					 origpagenumber, RelationGetRelationName(rel));
			}
			rightoff = OffsetNumberNext(rightoff);
		}
	}

	/* cope with possibility that newitem goes at the end */
	if (i <= newitemoff)
	{
		/*
		 * Can't have newitemonleft here; that would imply we were told to put
		 * *everything* on the left page, which cannot fit (if it could, we'd
		 * not be splitting the page).
		 */
		Assert(!newitemonleft);
		if (!_bt_pgaddtup(rightpage, newitemsz, newitem, rightoff))
		{
			memset(rightpage, 0, BufferGetPageSize(rbuf));
			elog(ERROR, "failed to add new item to the right sibling"
				 " while splitting block %u of index \"%s\"",
				 origpagenumber, RelationGetRelationName(rel));
		}
		rightoff = OffsetNumberNext(rightoff);
	}

	/*
	 * We have to grab the right sibling (if any) and fix the prev pointer
	 * there. We are guaranteed that this is deadlock-free since no other
	 * writer will be holding a lock on that page and trying to move left, and
	 * all readers release locks on a page before trying to fetch its
	 * neighbors.
	 */
	if (!P_RIGHTMOST(oopaque))
	{
		sbuf = _bt_getbuf(rel, oopaque->btpo_next, BT_WRITE);
		spage = BufferGetPage(sbuf);
		sopaque = (BTPageOpaque) PageGetSpecialPointer(spage);
		if (sopaque->btpo_prev != origpagenumber)
		{
			memset(rightpage, 0, BufferGetPageSize(rbuf));
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("right sibling's left-link doesn't match: "
									 "block %u links to %u instead of expected %u in index \"%s\"",
									 oopaque->btpo_next, sopaque->btpo_prev, origpagenumber,
									 RelationGetRelationName(rel))));
		}

		/*
		 * Check to see if we can set the SPLIT_END flag in the right-hand
		 * split page; this can save some I/O for vacuum since it need not
		 * proceed to the right sibling.  We can set the flag if the right
		 * sibling has a different cycleid: that means it could not be part of
		 * a group of pages that were all split off from the same ancestor
		 * page.  If you're confused, imagine that page A splits to A B and
		 * then again, yielding A C B, while vacuum is in progress.  Tuples
		 * originally in A could now be in either B or C, hence vacuum must
		 * examine both pages.  But if D, our right sibling, has a different
		 * cycleid then it could not contain any tuples that were in A when
		 * the vacuum started.
		 */
		if (sopaque->btpo_cycleid != ropaque->btpo_cycleid)
			ropaque->btpo_flags |= BTP_SPLIT_END;
	}

	/*
	 * Right sibling is locked, new siblings are prepared, but original page
	 * is not updated yet.
	 *
	 * NO EREPORT(ERROR) till right sibling is updated.  We can get away with
	 * not starting the critical section till here because we haven't been
	 * scribbling on the original page yet; see comments above.
	 */
	START_CRIT_SECTION();

	/*
	 * By here, the original data page has been split into two new halves, and
	 * these are correct.  The algorithm requires that the left page never
	 * move during a split, so we copy the new left page back on top of the
	 * original.  Note that this is not a waste of time, since we also require
	 * (in the page management code) that the center of a page always be
	 * clean, and the most efficient way to guarantee this is just to compact
	 * the data by reinserting it into a new left page.  (XXX the latter
	 * comment is probably obsolete; but in any case it's good to not scribble
	 * on the original page until we enter the critical section.)
	 *
	 * We need to do this before writing the WAL record, so that XLogInsert
	 * can WAL log an image of the page if necessary.
	 */
	PageRestoreTempPage(leftpage, origpage);
	/* leftpage, lopaque must not be used below here */

	MarkBufferDirty(buf);
	MarkBufferDirty(rbuf);

	if (!P_RIGHTMOST(ropaque))
	{
		sopaque->btpo_prev = rightpagenumber;
		MarkBufferDirty(sbuf);
	}

	/*
	 * Clear INCOMPLETE_SPLIT flag on child if inserting the new item finishes
	 * a split.
	 */
	if (!isleaf)
	{
		Page		cpage = BufferGetPage(cbuf);
		BTPageOpaque cpageop = (BTPageOpaque) PageGetSpecialPointer(cpage);

		cpageop->btpo_flags &= ~BTP_INCOMPLETE_SPLIT;
		MarkBufferDirty(cbuf);
	}

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_btree_split xlrec;
		uint8		xlinfo;
		XLogRecPtr	recptr;

		xlrec.level = ropaque->btpo.level;
		xlrec.firstright = firstright;
		xlrec.newitemoff = newitemoff;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBtreeSplit);

		XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
		XLogRegisterBuffer(1, rbuf, REGBUF_WILL_INIT);
		/* Log the right sibling, because we've changed its prev-pointer. */
		if (!P_RIGHTMOST(ropaque))
			XLogRegisterBuffer(2, sbuf, REGBUF_STANDARD);
		if (BufferIsValid(cbuf))
			XLogRegisterBuffer(3, cbuf, REGBUF_STANDARD);

		/*
		 * Log the new item, if it was inserted on the left page. (If it was
		 * put on the right page, we don't need to explicitly WAL log it
		 * because it's included with all the other items on the right page.)
		 * Show the new item as belonging to the left page buffer, so that it
		 * is not stored if XLogInsert decides it needs a full-page image of
		 * the left page.  We store the offset anyway, though, to support
		 * archive compression of these records.
		 */
		if (newitemonleft)
			XLogRegisterBufData(0, (char *) newitem, MAXALIGN(newitemsz));

		/* Log the left page's new high key */
		itemid = PageGetItemId(origpage, P_HIKEY);
		item = (IndexTuple) PageGetItem(origpage, itemid);
		XLogRegisterBufData(0, (char *) item, MAXALIGN(IndexTupleSize(item)));

		/*
		 * Log the contents of the right page in the format understood by
		 * _bt_restore_page().  The whole right page will be recreated.
		 *
		 * Direct access to page is not good but faster - we should implement
		 * some new func in page API.  Note we only store the tuples
		 * themselves, knowing that they were inserted in item-number order
		 * and so the line pointers can be reconstructed.  See comments for
		 * _bt_restore_page().
		 */
		XLogRegisterBufData(1,
							(char *) rightpage + ((PageHeader) rightpage)->pd_upper,
							((PageHeader) rightpage)->pd_special - ((PageHeader) rightpage)->pd_upper);

		xlinfo = newitemonleft ? XLOG_BTREE_SPLIT_L : XLOG_BTREE_SPLIT_R;
		recptr = XLogInsert(RM_BTREE_ID, xlinfo);

		PageSetLSN(origpage, recptr);
		PageSetLSN(rightpage, recptr);
		if (!P_RIGHTMOST(ropaque))
		{
			PageSetLSN(spage, recptr);
		}
		if (!isleaf)
		{
			PageSetLSN(BufferGetPage(cbuf), recptr);
		}
	}

	END_CRIT_SECTION();

	/* release the old right sibling */
	if (!P_RIGHTMOST(ropaque))
		_bt_relbuf(rel, sbuf);

	/* release the child */
	if (!isleaf)
		_bt_relbuf(rel, cbuf);

	/* split's done */
	return rbuf;
}