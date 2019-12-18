#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ rightblk; int /*<<< orphan*/  leftblk; scalar_t__ topparent; scalar_t__ leafblk; int /*<<< orphan*/  poffset; } ;
typedef  TYPE_1__ xl_btree_mark_page_halfdead ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_15__ {scalar_t__ btpo_next; int /*<<< orphan*/  btpo_prev; int /*<<< orphan*/  btpo_flags; } ;
struct TYPE_14__ {int t_info; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_2__ IndexTupleData ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_HALF_DEAD ; 
 scalar_t__ BTreeInnerTupleGetDownLink (scalar_t__) ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTreeTupleSetTopParent (TYPE_2__*,scalar_t__) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IndexTupleSize (TYPE_2__*) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_3__*) ; 
 scalar_t__ P_HIKEY ; 
 int /*<<< orphan*/  P_ISDELETED (TYPE_3__*) ; 
 int /*<<< orphan*/  P_ISHALFDEAD (TYPE_3__*) ; 
 scalar_t__ P_ISLEAF (TYPE_3__*) ; 
 int /*<<< orphan*/  P_ISROOT (TYPE_3__*) ; 
 int /*<<< orphan*/  P_RIGHTMOST (TYPE_3__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleOverwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPageCombine (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeMarkPageHalfDead ; 
 int /*<<< orphan*/  XLOG_BTREE_MARK_PAGE_HALFDEAD ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_is_page_halfdead (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_lock_branch_parent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_bt_mark_page_halfdead(Relation rel, Buffer leafbuf, BTStack stack)
{
	BlockNumber leafblkno;
	BlockNumber leafrightsib;
	BlockNumber target;
	BlockNumber rightsib;
	ItemId		itemid;
	Page		page;
	BTPageOpaque opaque;
	Buffer		topparent;
	OffsetNumber topoff;
	OffsetNumber nextoffset;
	IndexTuple	itup;
	IndexTupleData trunctuple;

	page = BufferGetPage(leafbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	Assert(!P_RIGHTMOST(opaque) && !P_ISROOT(opaque) && !P_ISDELETED(opaque) &&
		   !P_ISHALFDEAD(opaque) && P_ISLEAF(opaque) &&
		   P_FIRSTDATAKEY(opaque) > PageGetMaxOffsetNumber(page));

	/*
	 * Save info about the leaf page.
	 */
	leafblkno = BufferGetBlockNumber(leafbuf);
	leafrightsib = opaque->btpo_next;

	/*
	 * Before attempting to lock the parent page, check that the right sibling
	 * is not in half-dead state.  A half-dead right sibling would have no
	 * downlink in the parent, which would be highly confusing later when we
	 * delete the downlink that follows the current page's downlink. (I
	 * believe the deletion would work correctly, but it would fail the
	 * cross-check we make that the following downlink points to the right
	 * sibling of the delete page.)
	 */
	if (_bt_is_page_halfdead(rel, leafrightsib))
	{
		elog(DEBUG1, "could not delete page %u because its right sibling %u is half-dead",
			 leafblkno, leafrightsib);
		return false;
	}

	/*
	 * We cannot delete a page that is the rightmost child of its immediate
	 * parent, unless it is the only child --- in which case the parent has to
	 * be deleted too, and the same condition applies recursively to it. We
	 * have to check this condition all the way up before trying to delete,
	 * and lock the final parent of the to-be-deleted subtree.
	 *
	 * However, we won't need to repeat the above _bt_is_page_halfdead() check
	 * for parent/ancestor pages because of the rightmost restriction. The
	 * leaf check will apply to a right "cousin" leaf page rather than a
	 * simple right sibling leaf page in cases where we actually go on to
	 * perform internal page deletion. The right cousin leaf page is
	 * representative of the left edge of the subtree to the right of the
	 * to-be-deleted subtree as a whole.  (Besides, internal pages are never
	 * marked half-dead, so it isn't even possible to directly assess if an
	 * internal page is part of some other to-be-deleted subtree.)
	 */
	rightsib = leafrightsib;
	target = leafblkno;
	if (!_bt_lock_branch_parent(rel, leafblkno, stack,
								&topparent, &topoff, &target, &rightsib))
		return false;

	/*
	 * Check that the parent-page index items we're about to delete/overwrite
	 * contain what we expect.  This can fail if the index has become corrupt
	 * for some reason.  We want to throw any error before entering the
	 * critical section --- otherwise it'd be a PANIC.
	 *
	 * The test on the target item is just an Assert because
	 * _bt_lock_branch_parent should have guaranteed it has the expected
	 * contents.  The test on the next-child downlink is known to sometimes
	 * fail in the field, though.
	 */
	page = BufferGetPage(topparent);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

#ifdef USE_ASSERT_CHECKING
	itemid = PageGetItemId(page, topoff);
	itup = (IndexTuple) PageGetItem(page, itemid);
	Assert(BTreeInnerTupleGetDownLink(itup) == target);
#endif

	nextoffset = OffsetNumberNext(topoff);
	itemid = PageGetItemId(page, nextoffset);
	itup = (IndexTuple) PageGetItem(page, itemid);
	if (BTreeInnerTupleGetDownLink(itup) != rightsib)
		ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("right sibling %u of block %u is not next child %u of block %u in index \"%s\"",
									 rightsib, target, BTreeInnerTupleGetDownLink(itup),
					 BufferGetBlockNumber(topparent), RelationGetRelationName(rel))));

	/*
	 * Any insert which would have gone on the leaf block will now go to its
	 * right sibling.
	 */
	PredicateLockPageCombine(rel, leafblkno, leafrightsib);

	/* No ereport(ERROR) until changes are logged */
	START_CRIT_SECTION();

	/*
	 * Update parent.  The normal case is a tad tricky because we want to
	 * delete the target's downlink and the *following* key.  Easiest way is
	 * to copy the right sibling's downlink over the target downlink, and then
	 * delete the following item.
	 */
	page = BufferGetPage(topparent);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	itemid = PageGetItemId(page, topoff);
	itup = (IndexTuple) PageGetItem(page, itemid);
	BTreeInnerTupleSetDownLink(itup, rightsib);

	nextoffset = OffsetNumberNext(topoff);
	PageIndexTupleDelete(page, nextoffset);

	/*
	 * Mark the leaf page as half-dead, and stamp it with a pointer to the
	 * highest internal page in the branch we're deleting.  We use the tid of
	 * the high key to store it.
	 */
	page = BufferGetPage(leafbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_flags |= BTP_HALF_DEAD;

	Assert(PageGetMaxOffsetNumber(page) == P_HIKEY);
	MemSet(&trunctuple, 0, sizeof(IndexTupleData));
	trunctuple.t_info = sizeof(IndexTupleData);
	if (target != leafblkno)
		BTreeTupleSetTopParent(&trunctuple, target);
	else
		BTreeTupleSetTopParent(&trunctuple, InvalidBlockNumber);

	if (!PageIndexTupleOverwrite(page, P_HIKEY, (Item) &trunctuple,
								 IndexTupleSize(&trunctuple)))
		elog(ERROR, "could not overwrite high key in half-dead page");

	/* Must mark buffers dirty before XLogInsert */
	MarkBufferDirty(topparent);
	MarkBufferDirty(leafbuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_btree_mark_page_halfdead xlrec;
		XLogRecPtr	recptr;

		xlrec.poffset = topoff;
		xlrec.leafblk = leafblkno;
		if (target != leafblkno)
			xlrec.topparent = target;
		else
			xlrec.topparent = InvalidBlockNumber;

		XLogBeginInsert();
		XLogRegisterBuffer(0, leafbuf, REGBUF_WILL_INIT);
		XLogRegisterBuffer(1, topparent, REGBUF_STANDARD);

		page = BufferGetPage(leafbuf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		xlrec.leftblk = opaque->btpo_prev;
		xlrec.rightblk = opaque->btpo_next;

		XLogRegisterData((char *) &xlrec, SizeOfBtreeMarkPageHalfDead);

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_MARK_PAGE_HALFDEAD);

		page = BufferGetPage(topparent);
		PageSetLSN(page, recptr);
		page = BufferGetPage(leafbuf);
		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	_bt_relbuf(rel, topparent);
	return true;
}