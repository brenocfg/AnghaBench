#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t nToPlaceholder; scalar_t__ firstPlaceholder; int /*<<< orphan*/  newestRedirectXid; } ;
typedef  TYPE_1__ spgxlogVacuumRedirect ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {scalar_t__ tupstate; int /*<<< orphan*/  pointer; int /*<<< orphan*/  xid; } ;
struct TYPE_6__ {scalar_t__ nRedirection; scalar_t__ nPlaceholder; } ;
typedef  TYPE_2__* SpGistPageOpaque ;
typedef  TYPE_3__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_SPGIST_ID ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_PLACEHOLDER ; 
 scalar_t__ SPGIST_REDIRECT ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int SizeOfSpgxlogVacuumRedirect ; 
 TYPE_2__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_SPGIST_VACUUM_REDIRECT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

__attribute__((used)) static void
vacuumRedirectAndPlaceholder(Relation index, Buffer buffer)
{
	Page		page = BufferGetPage(buffer);
	SpGistPageOpaque opaque = SpGistPageGetOpaque(page);
	OffsetNumber i,
				max = PageGetMaxOffsetNumber(page),
				firstPlaceholder = InvalidOffsetNumber;
	bool		hasNonPlaceholder = false;
	bool		hasUpdate = false;
	OffsetNumber itemToPlaceholder[MaxIndexTuplesPerPage];
	OffsetNumber itemnos[MaxIndexTuplesPerPage];
	spgxlogVacuumRedirect xlrec;

	xlrec.nToPlaceholder = 0;
	xlrec.newestRedirectXid = InvalidTransactionId;

	START_CRIT_SECTION();

	/*
	 * Scan backwards to convert old redirection tuples to placeholder tuples,
	 * and identify location of last non-placeholder tuple while at it.
	 */
	for (i = max;
		 i >= FirstOffsetNumber &&
		 (opaque->nRedirection > 0 || !hasNonPlaceholder);
		 i--)
	{
		SpGistDeadTuple dt;

		dt = (SpGistDeadTuple) PageGetItem(page, PageGetItemId(page, i));

		if (dt->tupstate == SPGIST_REDIRECT &&
			TransactionIdPrecedes(dt->xid, RecentGlobalXmin))
		{
			dt->tupstate = SPGIST_PLACEHOLDER;
			Assert(opaque->nRedirection > 0);
			opaque->nRedirection--;
			opaque->nPlaceholder++;

			/* remember newest XID among the removed redirects */
			if (!TransactionIdIsValid(xlrec.newestRedirectXid) ||
				TransactionIdPrecedes(xlrec.newestRedirectXid, dt->xid))
				xlrec.newestRedirectXid = dt->xid;

			ItemPointerSetInvalid(&dt->pointer);

			itemToPlaceholder[xlrec.nToPlaceholder] = i;
			xlrec.nToPlaceholder++;

			hasUpdate = true;
		}

		if (dt->tupstate == SPGIST_PLACEHOLDER)
		{
			if (!hasNonPlaceholder)
				firstPlaceholder = i;
		}
		else
		{
			hasNonPlaceholder = true;
		}
	}

	/*
	 * Any placeholder tuples at the end of page can safely be removed.  We
	 * can't remove ones before the last non-placeholder, though, because we
	 * can't alter the offset numbers of non-placeholder tuples.
	 */
	if (firstPlaceholder != InvalidOffsetNumber)
	{
		/*
		 * We do not store this array to rdata because it's easy to recreate.
		 */
		for (i = firstPlaceholder; i <= max; i++)
			itemnos[i - firstPlaceholder] = i;

		i = max - firstPlaceholder + 1;
		Assert(opaque->nPlaceholder >= i);
		opaque->nPlaceholder -= i;

		/* The array is surely sorted, so can use PageIndexMultiDelete */
		PageIndexMultiDelete(page, itemnos, i);

		hasUpdate = true;
	}

	xlrec.firstPlaceholder = firstPlaceholder;

	if (hasUpdate)
		MarkBufferDirty(buffer);

	if (hasUpdate && RelationNeedsWAL(index))
	{
		XLogRecPtr	recptr;

		XLogBeginInsert();

		XLogRegisterData((char *) &xlrec, SizeOfSpgxlogVacuumRedirect);
		XLogRegisterData((char *) itemToPlaceholder,
						 sizeof(OffsetNumber) * xlrec.nToPlaceholder);

		XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

		recptr = XLogInsert(RM_SPGIST_ID, XLOG_SPGIST_VACUUM_REDIRECT);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();
}