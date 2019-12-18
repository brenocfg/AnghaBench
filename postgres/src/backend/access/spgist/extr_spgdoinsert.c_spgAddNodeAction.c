#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_20__ {scalar_t__ offnum; int parentBlk; scalar_t__ offnumParent; scalar_t__ offnumNew; int newPage; scalar_t__ nodeI; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogAddNode ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_24__ {scalar_t__ offnum; scalar_t__ buffer; scalar_t__ blkno; int /*<<< orphan*/  page; scalar_t__ node; } ;
struct TYPE_23__ {scalar_t__ size; } ;
struct TYPE_22__ {scalar_t__ size; } ;
struct TYPE_21__ {scalar_t__ isBuild; } ;
struct TYPE_19__ {int /*<<< orphan*/  nRedirection; int /*<<< orphan*/  nPlaceholder; } ;
typedef  TYPE_2__ SpGistState ;
typedef  TYPE_3__* SpGistInnerTuple ;
typedef  TYPE_4__* SpGistDeadTuple ;
typedef  TYPE_5__ SPPageDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GBUF_INNER_PARITY (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidBuffer ; 
 void* InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_SPGIST_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SPGIST_REDIRECT ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  STORE_STATE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistBlockIsRoot (scalar_t__) ; 
 scalar_t__ SpGistGetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ SpGistPageAddNewItem (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 TYPE_16__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistPageStoresNulls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistSetLastUsedPage (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  XLOG_SPGIST_ADD_NODE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 TYPE_3__* addNode (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  saveNodeLink (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,scalar_t__) ; 
 TYPE_4__* spgFormDeadTuple (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,void*) ; 

__attribute__((used)) static void
spgAddNodeAction(Relation index, SpGistState *state,
				 SpGistInnerTuple innerTuple,
				 SPPageDesc *current, SPPageDesc *parent,
				 int nodeN, Datum nodeLabel)
{
	SpGistInnerTuple newInnerTuple;
	spgxlogAddNode xlrec;

	/* Should not be applied to nulls */
	Assert(!SpGistPageStoresNulls(current->page));

	/* Construct new inner tuple with additional node */
	newInnerTuple = addNode(state, innerTuple, nodeLabel, nodeN);

	/* Prepare WAL record */
	STORE_STATE(state, xlrec.stateSrc);
	xlrec.offnum = current->offnum;

	/* we don't fill these unless we need to change the parent downlink */
	xlrec.parentBlk = -1;
	xlrec.offnumParent = InvalidOffsetNumber;
	xlrec.nodeI = 0;

	/* we don't fill these unless tuple has to be moved */
	xlrec.offnumNew = InvalidOffsetNumber;
	xlrec.newPage = false;

	if (PageGetExactFreeSpace(current->page) >=
		newInnerTuple->size - innerTuple->size)
	{
		/*
		 * We can replace the inner tuple by new version in-place
		 */
		START_CRIT_SECTION();

		PageIndexTupleDelete(current->page, current->offnum);
		if (PageAddItem(current->page,
						(Item) newInnerTuple, newInnerTuple->size,
						current->offnum, false, false) != current->offnum)
			elog(ERROR, "failed to add item of size %u to SPGiST index page",
				 newInnerTuple->size);

		MarkBufferDirty(current->buffer);

		if (RelationNeedsWAL(index) && !state->isBuild)
		{
			XLogRecPtr	recptr;

			XLogBeginInsert();
			XLogRegisterData((char *) &xlrec, sizeof(xlrec));
			XLogRegisterData((char *) newInnerTuple, newInnerTuple->size);

			XLogRegisterBuffer(0, current->buffer, REGBUF_STANDARD);

			recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_ADD_NODE);

			PageSetLSN(current->page, recptr);
		}

		END_CRIT_SECTION();
	}
	else
	{
		/*
		 * move inner tuple to another page, and update parent
		 */
		SpGistDeadTuple dt;
		SPPageDesc	saveCurrent;

		/*
		 * It should not be possible to get here for the root page, since we
		 * allow only one inner tuple on the root page, and spgFormInnerTuple
		 * always checks that inner tuples don't exceed the size of a page.
		 */
		if (SpGistBlockIsRoot(current->blkno))
			elog(ERROR, "cannot enlarge root tuple any more");
		Assert(parent->buffer != InvalidBuffer);

		saveCurrent = *current;

		xlrec.offnumParent = parent->offnum;
		xlrec.nodeI = parent->node;

		/*
		 * obtain new buffer with the same parity as current, since it will be
		 * a child of same parent tuple
		 */
		current->buffer = SpGistGetBuffer(index,
										  GBUF_INNER_PARITY(current->blkno),
										  newInnerTuple->size + sizeof(ItemIdData),
										  &xlrec.newPage);
		current->blkno = BufferGetBlockNumber(current->buffer);
		current->page = BufferGetPage(current->buffer);

		/*
		 * Let's just make real sure new current isn't same as old.  Right now
		 * that's impossible, but if SpGistGetBuffer ever got smart enough to
		 * delete placeholder tuples before checking space, maybe it wouldn't
		 * be impossible.  The case would appear to work except that WAL
		 * replay would be subtly wrong, so I think a mere assert isn't enough
		 * here.
		 */
		if (current->blkno == saveCurrent.blkno)
			elog(ERROR, "SPGiST new buffer shouldn't be same as old buffer");

		/*
		 * New current and parent buffer will both be modified; but note that
		 * parent buffer could be same as either new or old current.
		 */
		if (parent->buffer == saveCurrent.buffer)
			xlrec.parentBlk = 0;
		else if (parent->buffer == current->buffer)
			xlrec.parentBlk = 1;
		else
			xlrec.parentBlk = 2;

		START_CRIT_SECTION();

		/* insert new ... */
		xlrec.offnumNew = current->offnum =
			SpGistPageAddNewItem(state, current->page,
								 (Item) newInnerTuple, newInnerTuple->size,
								 NULL, false);

		MarkBufferDirty(current->buffer);

		/* update parent's downlink and mark parent page dirty */
		saveNodeLink(index, parent, current->blkno, current->offnum);

		/*
		 * Replace old tuple with a placeholder or redirection tuple.  Unless
		 * doing an index build, we have to insert a redirection tuple for
		 * possible concurrent scans.  We can't just delete it in any case,
		 * because that could change the offsets of other tuples on the page,
		 * breaking downlinks from their parents.
		 */
		if (state->isBuild)
			dt = spgFormDeadTuple(state, SPGIST_PLACEHOLDER,
								  InvalidBlockNumber, InvalidOffsetNumber);
		else
			dt = spgFormDeadTuple(state, SPGIST_REDIRECT,
								  current->blkno, current->offnum);

		PageIndexTupleDelete(saveCurrent.page, saveCurrent.offnum);
		if (PageAddItem(saveCurrent.page, (Item) dt, dt->size,
						saveCurrent.offnum,
						false, false) != saveCurrent.offnum)
			elog(ERROR, "failed to add item of size %u to SPGiST index page",
				 dt->size);

		if (state->isBuild)
			SpGistPageGetOpaque(saveCurrent.page)->nPlaceholder++;
		else
			SpGistPageGetOpaque(saveCurrent.page)->nRedirection++;

		MarkBufferDirty(saveCurrent.buffer);

		if (RelationNeedsWAL(index) && !state->isBuild)
		{
			XLogRecPtr	recptr;
			int			flags;

			XLogBeginInsert();

			/* orig page */
			XLogRegisterBuffer(0, saveCurrent.buffer, REGBUF_STANDARD);
			/* new page */
			flags = REGBUF_STANDARD;
			if (xlrec.newPage)
				flags |= REGBUF_WILL_INIT;
			XLogRegisterBuffer(1, current->buffer, flags);
			/* parent page (if different from orig and new) */
			if (xlrec.parentBlk == 2)
				XLogRegisterBuffer(2, parent->buffer, REGBUF_STANDARD);

			XLogRegisterData((char *) &xlrec, sizeof(xlrec));
			XLogRegisterData((char *) newInnerTuple, newInnerTuple->size);

			recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_ADD_NODE);

			/* we don't bother to check if any of these are redundant */
			PageSetLSN(current->page, recptr);
			PageSetLSN(parent->page, recptr);
			PageSetLSN(saveCurrent.page, recptr);
		}

		END_CRIT_SECTION();

		/* Release saveCurrent if it's not same as current or parent */
		if (saveCurrent.buffer != current->buffer &&
			saveCurrent.buffer != parent->buffer)
		{
			SpGistSetLastUsedPage(index, saveCurrent.buffer);
			UnlockReleaseBuffer(saveCurrent.buffer);
		}
	}
}