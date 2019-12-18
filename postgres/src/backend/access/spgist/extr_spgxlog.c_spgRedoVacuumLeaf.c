#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nDead; int nPlaceholder; int nMove; int nChain; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogVacuumLeaf ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_9__ {scalar_t__ tupstate; int /*<<< orphan*/  nextOffset; } ;
typedef  int /*<<< orphan*/  SpGistState ;
typedef  TYPE_3__* SpGistLeafTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/ * ItemId ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPGIST_DEAD ; 
 scalar_t__ SPGIST_LIVE ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SizeOfSpgxlogVacuumLeaf ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  fillFakeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgPageIndexMultiDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spgRedoVacuumLeaf(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogVacuumLeaf *xldata = (spgxlogVacuumLeaf *) ptr;
	OffsetNumber *toDead;
	OffsetNumber *toPlaceholder;
	OffsetNumber *moveSrc;
	OffsetNumber *moveDest;
	OffsetNumber *chainSrc;
	OffsetNumber *chainDest;
	SpGistState state;
	Buffer		buffer;
	Page		page;
	int			i;

	fillFakeState(&state, xldata->stateSrc);

	ptr += SizeOfSpgxlogVacuumLeaf;
	toDead = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nDead;
	toPlaceholder = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nPlaceholder;
	moveSrc = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nMove;
	moveDest = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nMove;
	chainSrc = (OffsetNumber *) ptr;
	ptr += sizeof(OffsetNumber) * xldata->nChain;
	chainDest = (OffsetNumber *) ptr;

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(buffer);

		spgPageIndexMultiDelete(&state, page,
								toDead, xldata->nDead,
								SPGIST_DEAD, SPGIST_DEAD,
								InvalidBlockNumber,
								InvalidOffsetNumber);

		spgPageIndexMultiDelete(&state, page,
								toPlaceholder, xldata->nPlaceholder,
								SPGIST_PLACEHOLDER, SPGIST_PLACEHOLDER,
								InvalidBlockNumber,
								InvalidOffsetNumber);

		/* see comments in vacuumLeafPage() */
		for (i = 0; i < xldata->nMove; i++)
		{
			ItemId		idSrc = PageGetItemId(page, moveSrc[i]);
			ItemId		idDest = PageGetItemId(page, moveDest[i]);
			ItemIdData	tmp;

			tmp = *idSrc;
			*idSrc = *idDest;
			*idDest = tmp;
		}

		spgPageIndexMultiDelete(&state, page,
								moveSrc, xldata->nMove,
								SPGIST_PLACEHOLDER, SPGIST_PLACEHOLDER,
								InvalidBlockNumber,
								InvalidOffsetNumber);

		for (i = 0; i < xldata->nChain; i++)
		{
			SpGistLeafTuple lt;

			lt = (SpGistLeafTuple) PageGetItem(page,
											   PageGetItemId(page, chainSrc[i]));
			Assert(lt->tupstate == SPGIST_LIVE);
			lt->nextOffset = chainDest[i];
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}