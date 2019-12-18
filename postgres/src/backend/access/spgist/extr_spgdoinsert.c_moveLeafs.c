#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int nMoves; int replaceDead; int storesNulls; int offnumParent; scalar_t__ newPage; int /*<<< orphan*/  nodeI; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogMoveLeafs ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_17__ {scalar_t__ buffer; int offnum; scalar_t__ blkno; int /*<<< orphan*/  page; int /*<<< orphan*/  node; } ;
struct TYPE_16__ {int size; scalar_t__ tupstate; int nextOffset; } ;
struct TYPE_15__ {scalar_t__ isBuild; } ;
typedef  TYPE_2__ SpGistState ;
typedef  TYPE_3__* SpGistLeafTuple ;
typedef  TYPE_4__ SPPageDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstOffsetNumber ; 
 int GBUF_LEAF ; 
 int GBUF_NULLS ; 
 scalar_t__ InvalidBuffer ; 
 int InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_SPGIST_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_DEAD ; 
 scalar_t__ SPGIST_LIVE ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SPGIST_REDIRECT ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  STORE_STATE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int SizeOfSpgxlogMoveLeafs ; 
 scalar_t__ SpGistGetBuffer (int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int SpGistPageAddNewItem (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  SpGistSetLastUsedPage (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  XLOG_SPGIST_MOVE_LEAFS ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_3__*,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  saveNodeLink (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  spgPageIndexMultiDelete (TYPE_2__*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
moveLeafs(Relation index, SpGistState *state,
		  SPPageDesc *current, SPPageDesc *parent,
		  SpGistLeafTuple newLeafTuple, bool isNulls)
{
	int			i,
				nDelete,
				nInsert,
				size;
	Buffer		nbuf;
	Page		npage;
	SpGistLeafTuple it;
	OffsetNumber r = InvalidOffsetNumber,
				startOffset = InvalidOffsetNumber;
	bool		replaceDead = false;
	OffsetNumber *toDelete;
	OffsetNumber *toInsert;
	BlockNumber nblkno;
	spgxlogMoveLeafs xlrec;
	char	   *leafdata,
			   *leafptr;

	/* This doesn't work on root page */
	Assert(parent->buffer != InvalidBuffer);
	Assert(parent->buffer != current->buffer);

	/* Locate the tuples to be moved, and count up the space needed */
	i = PageGetMaxOffsetNumber(current->page);
	toDelete = (OffsetNumber *) palloc(sizeof(OffsetNumber) * i);
	toInsert = (OffsetNumber *) palloc(sizeof(OffsetNumber) * (i + 1));

	size = newLeafTuple->size + sizeof(ItemIdData);

	nDelete = 0;
	i = current->offnum;
	while (i != InvalidOffsetNumber)
	{
		SpGistLeafTuple it;

		Assert(i >= FirstOffsetNumber &&
			   i <= PageGetMaxOffsetNumber(current->page));
		it = (SpGistLeafTuple) PageGetItem(current->page,
										   PageGetItemId(current->page, i));

		if (it->tupstate == SPGIST_LIVE)
		{
			toDelete[nDelete] = i;
			size += it->size + sizeof(ItemIdData);
			nDelete++;
		}
		else if (it->tupstate == SPGIST_DEAD)
		{
			/* We could see a DEAD tuple as first/only chain item */
			Assert(i == current->offnum);
			Assert(it->nextOffset == InvalidOffsetNumber);
			/* We don't want to move it, so don't count it in size */
			toDelete[nDelete] = i;
			nDelete++;
			replaceDead = true;
		}
		else
			elog(ERROR, "unexpected SPGiST tuple state: %d", it->tupstate);

		i = it->nextOffset;
	}

	/* Find a leaf page that will hold them */
	nbuf = SpGistGetBuffer(index, GBUF_LEAF | (isNulls ? GBUF_NULLS : 0),
						   size, &xlrec.newPage);
	npage = BufferGetPage(nbuf);
	nblkno = BufferGetBlockNumber(nbuf);
	Assert(nblkno != current->blkno);

	leafdata = leafptr = palloc(size);

	START_CRIT_SECTION();

	/* copy all the old tuples to new page, unless they're dead */
	nInsert = 0;
	if (!replaceDead)
	{
		for (i = 0; i < nDelete; i++)
		{
			it = (SpGistLeafTuple) PageGetItem(current->page,
											   PageGetItemId(current->page, toDelete[i]));
			Assert(it->tupstate == SPGIST_LIVE);

			/*
			 * Update chain link (notice the chain order gets reversed, but we
			 * don't care).  We're modifying the tuple on the source page
			 * here, but it's okay since we're about to delete it.
			 */
			it->nextOffset = r;

			r = SpGistPageAddNewItem(state, npage, (Item) it, it->size,
									 &startOffset, false);

			toInsert[nInsert] = r;
			nInsert++;

			/* save modified tuple into leafdata as well */
			memcpy(leafptr, it, it->size);
			leafptr += it->size;
		}
	}

	/* add the new tuple as well */
	newLeafTuple->nextOffset = r;
	r = SpGistPageAddNewItem(state, npage,
							 (Item) newLeafTuple, newLeafTuple->size,
							 &startOffset, false);
	toInsert[nInsert] = r;
	nInsert++;
	memcpy(leafptr, newLeafTuple, newLeafTuple->size);
	leafptr += newLeafTuple->size;

	/*
	 * Now delete the old tuples, leaving a redirection pointer behind for the
	 * first one, unless we're doing an index build; in which case there can't
	 * be any concurrent scan so we need not provide a redirect.
	 */
	spgPageIndexMultiDelete(state, current->page, toDelete, nDelete,
							state->isBuild ? SPGIST_PLACEHOLDER : SPGIST_REDIRECT,
							SPGIST_PLACEHOLDER,
							nblkno, r);

	/* Update parent's downlink and mark parent page dirty */
	saveNodeLink(index, parent, nblkno, r);

	/* Mark the leaf pages too */
	MarkBufferDirty(current->buffer);
	MarkBufferDirty(nbuf);

	if (RelationNeedsWAL(index) && !state->isBuild)
	{
		XLogRecPtr	recptr;

		/* prepare WAL info */
		STORE_STATE(state, xlrec.stateSrc);

		xlrec.nMoves = nDelete;
		xlrec.replaceDead = replaceDead;
		xlrec.storesNulls = isNulls;

		xlrec.offnumParent = parent->offnum;
		xlrec.nodeI = parent->node;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfSpgxlogMoveLeafs);
		XLogRegisterData((char *) toDelete,
						 sizeof(OffsetNumber) * nDelete);
		XLogRegisterData((char *) toInsert,
						 sizeof(OffsetNumber) * nInsert);
		XLogRegisterData((char *) leafdata, leafptr - leafdata);

		XLogRegisterBuffer(0, current->buffer, REGBUF_STANDARD);
		XLogRegisterBuffer(1, nbuf, REGBUF_STANDARD | (xlrec.newPage ? REGBUF_WILL_INIT : 0));
		XLogRegisterBuffer(2, parent->buffer, REGBUF_STANDARD);

		recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_MOVE_LEAFS);

		PageSetLSN(current->page, recptr);
		PageSetLSN(npage, recptr);
		PageSetLSN(parent->page, recptr);
	}

	END_CRIT_SECTION();

	/* Update local free-space cache and release new buffer */
	SpGistSetLastUsedPage(index, nbuf);
	UnlockReleaseBuffer(nbuf);
}