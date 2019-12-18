#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t nDelete; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_2__ spgxlogVacuumRoot ;
struct TYPE_8__ {int /*<<< orphan*/  spgstate; TYPE_1__* stats; int /*<<< orphan*/  callback_state; scalar_t__ (* callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ spgBulkDeleteState ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {scalar_t__ tupstate; int /*<<< orphan*/  heapPtr; } ;
struct TYPE_6__ {int tuples_removed; int num_index_tuples; } ;
typedef  TYPE_4__* SpGistLeafTuple ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_SPGIST_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_LIVE ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  STORE_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SizeOfSpgxlogVacuumRoot ; 
 int /*<<< orphan*/  XLOG_SPGIST_VACUUM_ROOT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vacuumLeafRoot(spgBulkDeleteState *bds, Relation index, Buffer buffer)
{
	Page		page = BufferGetPage(buffer);
	spgxlogVacuumRoot xlrec;
	OffsetNumber toDelete[MaxIndexTuplesPerPage];
	OffsetNumber i,
				max = PageGetMaxOffsetNumber(page);

	xlrec.nDelete = 0;

	/* Scan page, identify tuples to delete, accumulate stats */
	for (i = FirstOffsetNumber; i <= max; i++)
	{
		SpGistLeafTuple lt;

		lt = (SpGistLeafTuple) PageGetItem(page,
										   PageGetItemId(page, i));
		if (lt->tupstate == SPGIST_LIVE)
		{
			Assert(ItemPointerIsValid(&lt->heapPtr));

			if (bds->callback(&lt->heapPtr, bds->callback_state))
			{
				bds->stats->tuples_removed += 1;
				toDelete[xlrec.nDelete] = i;
				xlrec.nDelete++;
			}
			else
			{
				bds->stats->num_index_tuples += 1;
			}
		}
		else
		{
			/* all tuples on root should be live */
			elog(ERROR, "unexpected SPGiST tuple state: %d",
				 lt->tupstate);
		}
	}

	if (xlrec.nDelete == 0)
		return;					/* nothing more to do */

	/* Do the update */
	START_CRIT_SECTION();

	/* The tuple numbers are in order, so we can use PageIndexMultiDelete */
	PageIndexMultiDelete(page, toDelete, xlrec.nDelete);

	MarkBufferDirty(buffer);

	if (RelationNeedsWAL(index))
	{
		XLogRecPtr	recptr;

		XLogBeginInsert();

		/* Prepare WAL record */
		STORE_STATE(&bds->spgstate, xlrec.stateSrc);

		XLogRegisterData((char *) &xlrec, SizeOfSpgxlogVacuumRoot);
		/* sizeof(xlrec) should be a multiple of sizeof(OffsetNumber) */
		XLogRegisterData((char *) toDelete,
						 sizeof(OffsetNumber) * xlrec.nDelete);

		XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

		recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_VACUUM_ROOT);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();
}