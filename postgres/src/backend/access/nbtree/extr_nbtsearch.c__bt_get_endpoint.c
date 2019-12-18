#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_6__ {scalar_t__ level; } ;
struct TYPE_7__ {scalar_t__ btpo_next; TYPE_1__ btpo; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BT_READ ; 
 scalar_t__ BTreeInnerTupleGetDownLink (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  P_FIRSTDATAKEY (TYPE_2__*) ; 
 scalar_t__ P_IGNORE (TYPE_2__*) ; 
 scalar_t__ P_NONE ; 
 int /*<<< orphan*/  P_RIGHTMOST (TYPE_2__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getroot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_gettrueroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relandgetbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,scalar_t__,int /*<<< orphan*/ ) ; 

Buffer
_bt_get_endpoint(Relation rel, uint32 level, bool rightmost,
				 Snapshot snapshot)
{
	Buffer		buf;
	Page		page;
	BTPageOpaque opaque;
	OffsetNumber offnum;
	BlockNumber blkno;
	IndexTuple	itup;

	/*
	 * If we are looking for a leaf page, okay to descend from fast root;
	 * otherwise better descend from true root.  (There is no point in being
	 * smarter about intermediate levels.)
	 */
	if (level == 0)
		buf = _bt_getroot(rel, BT_READ);
	else
		buf = _bt_gettrueroot(rel);

	if (!BufferIsValid(buf))
		return InvalidBuffer;

	page = BufferGetPage(buf);
	TestForOldSnapshot(snapshot, rel, page);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	for (;;)
	{
		/*
		 * If we landed on a deleted page, step right to find a live page
		 * (there must be one).  Also, if we want the rightmost page, step
		 * right if needed to get to it (this could happen if the page split
		 * since we obtained a pointer to it).
		 */
		while (P_IGNORE(opaque) ||
			   (rightmost && !P_RIGHTMOST(opaque)))
		{
			blkno = opaque->btpo_next;
			if (blkno == P_NONE)
				elog(ERROR, "fell off the end of index \"%s\"",
					 RelationGetRelationName(rel));
			buf = _bt_relandgetbuf(rel, buf, blkno, BT_READ);
			page = BufferGetPage(buf);
			TestForOldSnapshot(snapshot, rel, page);
			opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		}

		/* Done? */
		if (opaque->btpo.level == level)
			break;
		if (opaque->btpo.level < level)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("btree level %u not found in index \"%s\"",
									 level, RelationGetRelationName(rel))));

		/* Descend to leftmost or rightmost child page */
		if (rightmost)
			offnum = PageGetMaxOffsetNumber(page);
		else
			offnum = P_FIRSTDATAKEY(opaque);

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, offnum));
		blkno = BTreeInnerTupleGetDownLink(itup);

		buf = _bt_relandgetbuf(rel, buf, blkno, BT_READ);
		page = BufferGetPage(buf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	}

	return buf;
}