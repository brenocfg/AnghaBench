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
struct TYPE_13__ {int nMoves; int /*<<< orphan*/  nodeI; int /*<<< orphan*/  offnumParent; scalar_t__ storesNulls; scalar_t__ newPage; scalar_t__ replaceDead; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogMoveLeafs ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_14__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_16__ {int /*<<< orphan*/  size; } ;
struct TYPE_15__ {scalar_t__ isBuild; } ;
typedef  TYPE_3__ SpGistState ;
typedef  TYPE_4__ SpGistLeafTupleData ;
typedef  scalar_t__ SpGistInnerTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 int SPGIST_NULLS ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SPGIST_REDIRECT ; 
 int /*<<< orphan*/  SizeOfSpgxlogMoveLeafs ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  addOrReplaceTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillFakeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  spgPageIndexMultiDelete (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgUpdateNodeLink (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spgRedoMoveLeafs(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogMoveLeafs *xldata = (spgxlogMoveLeafs *) ptr;
	SpGistState state;
	OffsetNumber *toDelete;
	OffsetNumber *toInsert;
	int			nInsert;
	Buffer		buffer;
	Page		page;
	XLogRedoAction action;
	BlockNumber blknoDst;

	XLogRecGetBlockTag(record, 1, NULL, NULL, &blknoDst);

	fillFakeState(&state, xldata->stateSrc);

	nInsert = xldata->replaceDead ? 1 : xldata->nMoves + 1;

	ptr += SizeOfSpgxlogMoveLeafs;
	toDelete = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nMoves;
	toInsert = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * nInsert;

	/* now ptr points to the list of leaf tuples */

	/*
	 * In normal operation we would have all three pages (source, dest, and
	 * parent) locked simultaneously; but in WAL replay it should be safe to
	 * update them one at a time, as long as we do it in the right order.
	 */

	/* Insert tuples on the dest page (do first, so redirect is valid) */
	if (xldata->newPage)
	{
		buffer = XLogInitBufferForRedo(record, 1);
		SpGistInitBuffer(buffer,
						 SPGIST_LEAF | (xldata->storesNulls ? SPGIST_NULLS : 0));
		action = BLK_NEEDS_REDO;
	}
	else
		action = XLogReadBufferForRedo(record, 1, &buffer);

	if (action == BLK_NEEDS_REDO)
	{
		int			i;

		page = BufferGetPage(buffer);

		for (i = 0; i < nInsert; i++)
		{
			char	   *leafTuple;
			SpGistLeafTupleData leafTupleHdr;

			/*
			 * the tuples are not aligned, so must copy to access the size
			 * field.
			 */
			leafTuple = ptr;
			memcpy(&leafTupleHdr, leafTuple,
				   sizeof(SpGistLeafTupleData));

			addOrReplaceTuple(page, (Item) leafTuple,
							  leafTupleHdr.size, toInsert[i]);
			ptr += leafTupleHdr.size;
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* Delete tuples from the source page, inserting a redirection pointer */
	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(buffer);

		spgPageIndexMultiDelete(&state, page, toDelete, xldata->nMoves,
								state.isBuild ? SPGIST_PLACEHOLDER : SPGIST_REDIRECT,
								SPGIST_PLACEHOLDER,
								blknoDst,
								toInsert[nInsert - 1]);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* And update the parent downlink */
	if (XLogReadBufferForRedo(record, 2, &buffer) == BLK_NEEDS_REDO)
	{
		SpGistInnerTuple tuple;

		page = BufferGetPage(buffer);

		tuple = (SpGistInnerTuple) PageGetItem(page,
											   PageGetItemId(page, xldata->offnumParent));

		spgUpdateNodeLink(tuple, xldata->nodeI,
						  blknoDst, toInsert[nInsert - 1]);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}