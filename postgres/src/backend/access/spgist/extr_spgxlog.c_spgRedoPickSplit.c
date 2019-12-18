#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
struct TYPE_15__ {int nDelete; int nInsert; scalar_t__ isRootSplit; scalar_t__ innerIsParent; int /*<<< orphan*/  offnumInner; int /*<<< orphan*/  nodeI; int /*<<< orphan*/  offnumParent; scalar_t__ storesNulls; scalar_t__ initInner; scalar_t__ initDest; scalar_t__ initSrc; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogPickSplit ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_16__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_18__ {int /*<<< orphan*/  size; } ;
struct TYPE_17__ {int /*<<< orphan*/  isBuild; } ;
typedef  TYPE_3__ SpGistState ;
typedef  TYPE_4__ SpGistLeafTupleData ;
typedef  TYPE_4__ SpGistInnerTupleData ;
typedef  scalar_t__ SpGistInnerTuple ;
typedef  int /*<<< orphan*/ * Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/ * BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 int SPGIST_NULLS ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SPGIST_REDIRECT ; 
 int /*<<< orphan*/  SizeOfSpgxlogPickSplit ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 scalar_t__ XLogRecHasBlockRef (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addOrReplaceTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillFakeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  spgPageIndexMultiDelete (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgUpdateNodeLink (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spgRedoPickSplit(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogPickSplit *xldata = (spgxlogPickSplit *) ptr;
	char	   *innerTuple;
	SpGistInnerTupleData innerTupleHdr;
	SpGistState state;
	OffsetNumber *toDelete;
	OffsetNumber *toInsert;
	uint8	   *leafPageSelect;
	Buffer		srcBuffer;
	Buffer		destBuffer;
	Buffer		innerBuffer;
	Page		srcPage;
	Page		destPage;
	Page		page;
	int			i;
	BlockNumber blknoInner;
	XLogRedoAction action;

	XLogRecGetBlockTag(record, 2, NULL, NULL, &blknoInner);

	fillFakeState(&state, xldata->stateSrc);

	ptr += SizeOfSpgxlogPickSplit;
	toDelete = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nDelete;
	toInsert = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nInsert;
	leafPageSelect = (uint8 *) ptr;
	ptr += sizeof(uint8) * xldata->nInsert;

	innerTuple = ptr;
	/* the inner tuple is unaligned, so make a copy to access its header */
	memcpy(&innerTupleHdr, innerTuple, sizeof(SpGistInnerTupleData));
	ptr += innerTupleHdr.size;

	/* now ptr points to the list of leaf tuples */

	if (xldata->isRootSplit)
	{
		/* when splitting root, we touch it only in the guise of new inner */
		srcBuffer = InvalidBuffer;
		srcPage = NULL;
	}
	else if (xldata->initSrc)
	{
		/* just re-init the source page */
		srcBuffer = XLogInitBufferForRedo(record, 0);
		srcPage = (Page) BufferGetPage(srcBuffer);

		SpGistInitBuffer(srcBuffer,
						 SPGIST_LEAF | (xldata->storesNulls ? SPGIST_NULLS : 0));
		/* don't update LSN etc till we're done with it */
	}
	else
	{
		/*
		 * Delete the specified tuples from source page.  (In case we're in
		 * Hot Standby, we need to hold lock on the page till we're done
		 * inserting leaf tuples and the new inner tuple, else the added
		 * redirect tuple will be a dangling link.)
		 */
		srcPage = NULL;
		if (XLogReadBufferForRedo(record, 0, &srcBuffer) == BLK_NEEDS_REDO)
		{
			srcPage = BufferGetPage(srcBuffer);

			/*
			 * We have it a bit easier here than in doPickSplit(), because we
			 * know the inner tuple's location already, so we can inject the
			 * correct redirection tuple now.
			 */
			if (!state.isBuild)
				spgPageIndexMultiDelete(&state, srcPage,
										toDelete, xldata->nDelete,
										SPGIST_REDIRECT,
										SPGIST_PLACEHOLDER,
										blknoInner,
										xldata->offnumInner);
			else
				spgPageIndexMultiDelete(&state, srcPage,
										toDelete, xldata->nDelete,
										SPGIST_PLACEHOLDER,
										SPGIST_PLACEHOLDER,
										InvalidBlockNumber,
										InvalidOffsetNumber);

			/* don't update LSN etc till we're done with it */
		}
	}

	/* try to access dest page if any */
	if (!XLogRecHasBlockRef(record, 1))
	{
		destBuffer = InvalidBuffer;
		destPage = NULL;
	}
	else if (xldata->initDest)
	{
		/* just re-init the dest page */
		destBuffer = XLogInitBufferForRedo(record, 1);
		destPage = (Page) BufferGetPage(destBuffer);

		SpGistInitBuffer(destBuffer,
						 SPGIST_LEAF | (xldata->storesNulls ? SPGIST_NULLS : 0));
		/* don't update LSN etc till we're done with it */
	}
	else
	{
		/*
		 * We could probably release the page lock immediately in the
		 * full-page-image case, but for safety let's hold it till later.
		 */
		if (XLogReadBufferForRedo(record, 1, &destBuffer) == BLK_NEEDS_REDO)
			destPage = (Page) BufferGetPage(destBuffer);
		else
			destPage = NULL;	/* don't do any page updates */
	}

	/* restore leaf tuples to src and/or dest page */
	for (i = 0; i < xldata->nInsert; i++)
	{
		char	   *leafTuple;
		SpGistLeafTupleData leafTupleHdr;

		/* the tuples are not aligned, so must copy to access the size field. */
		leafTuple = ptr;
		memcpy(&leafTupleHdr, leafTuple, sizeof(SpGistLeafTupleData));
		ptr += leafTupleHdr.size;

		page = leafPageSelect[i] ? destPage : srcPage;
		if (page == NULL)
			continue;			/* no need to touch this page */

		addOrReplaceTuple(page, (Item) leafTuple, leafTupleHdr.size,
						  toInsert[i]);
	}

	/* Now update src and dest page LSNs if needed */
	if (srcPage != NULL)
	{
		PageSetLSN(srcPage, lsn);
		MarkBufferDirty(srcBuffer);
	}
	if (destPage != NULL)
	{
		PageSetLSN(destPage, lsn);
		MarkBufferDirty(destBuffer);
	}

	/* restore new inner tuple */
	if (xldata->initInner)
	{
		innerBuffer = XLogInitBufferForRedo(record, 2);
		SpGistInitBuffer(innerBuffer, (xldata->storesNulls ? SPGIST_NULLS : 0));
		action = BLK_NEEDS_REDO;
	}
	else
		action = XLogReadBufferForRedo(record, 2, &innerBuffer);

	if (action == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(innerBuffer);

		addOrReplaceTuple(page, (Item) innerTuple, innerTupleHdr.size,
						  xldata->offnumInner);

		/* if inner is also parent, update link while we're here */
		if (xldata->innerIsParent)
		{
			SpGistInnerTuple parent;

			parent = (SpGistInnerTuple) PageGetItem(page,
													PageGetItemId(page, xldata->offnumParent));
			spgUpdateNodeLink(parent, xldata->nodeI,
							  blknoInner, xldata->offnumInner);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(innerBuffer);
	}
	if (BufferIsValid(innerBuffer))
		UnlockReleaseBuffer(innerBuffer);

	/*
	 * Now we can release the leaf-page locks.  It's okay to do this before
	 * updating the parent downlink.
	 */
	if (BufferIsValid(srcBuffer))
		UnlockReleaseBuffer(srcBuffer);
	if (BufferIsValid(destBuffer))
		UnlockReleaseBuffer(destBuffer);

	/* update parent downlink, unless we did it above */
	if (XLogRecHasBlockRef(record, 3))
	{
		Buffer		parentBuffer;

		if (XLogReadBufferForRedo(record, 3, &parentBuffer) == BLK_NEEDS_REDO)
		{
			SpGistInnerTuple parent;

			page = BufferGetPage(parentBuffer);

			parent = (SpGistInnerTuple) PageGetItem(page,
													PageGetItemId(page, xldata->offnumParent));
			spgUpdateNodeLink(parent, xldata->nodeI,
							  blknoInner, xldata->offnumInner);

			PageSetLSN(page, lsn);
			MarkBufferDirty(parentBuffer);
		}
		if (BufferIsValid(parentBuffer))
			UnlockReleaseBuffer(parentBuffer);
	}
	else
		Assert(xldata->innerIsParent || xldata->isRootSplit);
}