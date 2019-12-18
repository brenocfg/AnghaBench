#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* offsets; int nToPlaceholder; int firstPlaceholder; int /*<<< orphan*/  newestRedirectXid; } ;
typedef  TYPE_1__ spgxlogVacuumRedirect ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_11__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_13__ {scalar_t__ tupstate; int /*<<< orphan*/  pointer; } ;
struct TYPE_12__ {int nRedirection; int nPlaceholder; } ;
typedef  TYPE_3__* SpGistPageOpaque ;
typedef  TYPE_4__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InHotStandby ; 
 int InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_PLACEHOLDER ; 
 scalar_t__ SPGIST_REDIRECT ; 
 TYPE_3__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 

__attribute__((used)) static void
spgRedoVacuumRedirect(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogVacuumRedirect *xldata = (spgxlogVacuumRedirect *) ptr;
	OffsetNumber *itemToPlaceholder;
	Buffer		buffer;

	itemToPlaceholder = xldata->offsets;

	/*
	 * If any redirection tuples are being removed, make sure there are no
	 * live Hot Standby transactions that might need to see them.
	 */
	if (InHotStandby)
	{
		if (TransactionIdIsValid(xldata->newestRedirectXid))
		{
			RelFileNode node;

			XLogRecGetBlockTag(record, 0, &node, NULL, NULL);
			ResolveRecoveryConflictWithSnapshot(xldata->newestRedirectXid,
												node);
		}
	}

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		Page		page = BufferGetPage(buffer);
		SpGistPageOpaque opaque = SpGistPageGetOpaque(page);
		int			i;

		/* Convert redirect pointers to plain placeholders */
		for (i = 0; i < xldata->nToPlaceholder; i++)
		{
			SpGistDeadTuple dt;

			dt = (SpGistDeadTuple) PageGetItem(page,
											   PageGetItemId(page, itemToPlaceholder[i]));
			Assert(dt->tupstate == SPGIST_REDIRECT);
			dt->tupstate = SPGIST_PLACEHOLDER;
			ItemPointerSetInvalid(&dt->pointer);
		}

		Assert(opaque->nRedirection >= xldata->nToPlaceholder);
		opaque->nRedirection -= xldata->nToPlaceholder;
		opaque->nPlaceholder += xldata->nToPlaceholder;

		/* Remove placeholder tuples at end of page */
		if (xldata->firstPlaceholder != InvalidOffsetNumber)
		{
			int			max = PageGetMaxOffsetNumber(page);
			OffsetNumber *toDelete;

			toDelete = palloc(sizeof(OffsetNumber) * max);

			for (i = xldata->firstPlaceholder; i <= max; i++)
				toDelete[i - xldata->firstPlaceholder] = i;

			i = max - xldata->firstPlaceholder + 1;
			Assert(opaque->nPlaceholder >= i);
			opaque->nPlaceholder -= i;

			/* The array is sorted, so can use PageIndexMultiDelete */
			PageIndexMultiDelete(page, toDelete, i);

			pfree(toDelete);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}