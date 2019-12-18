#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_11__ {int newPage; int storesNulls; scalar_t__ offnumLeaf; scalar_t__ offnumHeadLeaf; scalar_t__ offnumParent; scalar_t__ nodeI; } ;
typedef  TYPE_1__ spgxlogAddLeaf ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_14__ {scalar_t__ offnum; scalar_t__ buffer; int /*<<< orphan*/  page; int /*<<< orphan*/  blkno; scalar_t__ node; } ;
struct TYPE_13__ {int size; scalar_t__ tupstate; void* nextOffset; } ;
struct TYPE_12__ {int /*<<< orphan*/  isBuild; } ;
typedef  TYPE_2__ SpGistState ;
typedef  TYPE_3__* SpGistLeafTuple ;
typedef  TYPE_4__ SPPageDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;

/* Variables and functions */
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_SPGIST_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_DEAD ; 
 scalar_t__ SPGIST_LIVE ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 scalar_t__ SpGistBlockIsRoot (int /*<<< orphan*/ ) ; 
 void* SpGistPageAddNewItem (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XLOG_SPGIST_ADD_LEAF ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  saveNodeLink (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
addLeafTuple(Relation index, SpGistState *state, SpGistLeafTuple leafTuple,
			 SPPageDesc *current, SPPageDesc *parent, bool isNulls, bool isNew)
{
	spgxlogAddLeaf xlrec;

	xlrec.newPage = isNew;
	xlrec.storesNulls = isNulls;

	/* these will be filled below as needed */
	xlrec.offnumLeaf = InvalidOffsetNumber;
	xlrec.offnumHeadLeaf = InvalidOffsetNumber;
	xlrec.offnumParent = InvalidOffsetNumber;
	xlrec.nodeI = 0;

	START_CRIT_SECTION();

	if (current->offnum == InvalidOffsetNumber ||
		SpGistBlockIsRoot(current->blkno))
	{
		/* Tuple is not part of a chain */
		leafTuple->nextOffset = InvalidOffsetNumber;
		current->offnum = SpGistPageAddNewItem(state, current->page,
											   (Item) leafTuple, leafTuple->size,
											   NULL, false);

		xlrec.offnumLeaf = current->offnum;

		/* Must update parent's downlink if any */
		if (parent->buffer != InvalidBuffer)
		{
			xlrec.offnumParent = parent->offnum;
			xlrec.nodeI = parent->node;

			saveNodeLink(index, parent, current->blkno, current->offnum);
		}
	}
	else
	{
		/*
		 * Tuple must be inserted into existing chain.  We mustn't change the
		 * chain's head address, but we don't need to chase the entire chain
		 * to put the tuple at the end; we can insert it second.
		 *
		 * Also, it's possible that the "chain" consists only of a DEAD tuple,
		 * in which case we should replace the DEAD tuple in-place.
		 */
		SpGistLeafTuple head;
		OffsetNumber offnum;

		head = (SpGistLeafTuple) PageGetItem(current->page,
											 PageGetItemId(current->page, current->offnum));
		if (head->tupstate == SPGIST_LIVE)
		{
			leafTuple->nextOffset = head->nextOffset;
			offnum = SpGistPageAddNewItem(state, current->page,
										  (Item) leafTuple, leafTuple->size,
										  NULL, false);

			/*
			 * re-get head of list because it could have been moved on page,
			 * and set new second element
			 */
			head = (SpGistLeafTuple) PageGetItem(current->page,
												 PageGetItemId(current->page, current->offnum));
			head->nextOffset = offnum;

			xlrec.offnumLeaf = offnum;
			xlrec.offnumHeadLeaf = current->offnum;
		}
		else if (head->tupstate == SPGIST_DEAD)
		{
			leafTuple->nextOffset = InvalidOffsetNumber;
			PageIndexTupleDelete(current->page, current->offnum);
			if (PageAddItem(current->page,
							(Item) leafTuple, leafTuple->size,
							current->offnum, false, false) != current->offnum)
				elog(ERROR, "failed to add item of size %u to SPGiST index page",
					 leafTuple->size);

			/* WAL replay distinguishes this case by equal offnums */
			xlrec.offnumLeaf = current->offnum;
			xlrec.offnumHeadLeaf = current->offnum;
		}
		else
			elog(ERROR, "unexpected SPGiST tuple state: %d", head->tupstate);
	}

	MarkBufferDirty(current->buffer);

	if (RelationNeedsWAL(index) && !state->isBuild)
	{
		XLogRecPtr	recptr;
		int			flags;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, sizeof(xlrec));
		XLogRegisterData((char *) leafTuple, leafTuple->size);

		flags = REGBUF_STANDARD;
		if (xlrec.newPage)
			flags |= REGBUF_WILL_INIT;
		XLogRegisterBuffer(0, current->buffer, flags);
		if (xlrec.offnumParent != InvalidOffsetNumber)
			XLogRegisterBuffer(1, parent->buffer, REGBUF_STANDARD);

		recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_ADD_LEAF);

		PageSetLSN(current->page, recptr);

		/* update parent only if we actually changed it */
		if (xlrec.offnumParent != InvalidOffsetNumber)
		{
			PageSetLSN(parent->page, recptr);
		}
	}

	END_CRIT_SECTION();
}