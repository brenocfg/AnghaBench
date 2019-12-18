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
struct TYPE_5__ {int ntuples; int /*<<< orphan*/  latestRemovedXid; } ;
typedef  TYPE_1__ xl_hash_vacuum_one_page ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int hashm_ntuples; } ;
struct TYPE_6__ {int /*<<< orphan*/  hasho_flag; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  TYPE_3__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 TYPE_3__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_PAGE_HAS_DEAD_TUPLES ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int MaxOffsetNumber ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int SizeOfHashVacuumOnePage ; 
 int /*<<< orphan*/  XLOG_HASH_VACUUM_ONE_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  index_compute_xid_horizon_for_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
_hash_vacuum_one_page(Relation rel, Relation hrel, Buffer metabuf, Buffer buf)
{
	OffsetNumber deletable[MaxOffsetNumber];
	int			ndeletable = 0;
	OffsetNumber offnum,
				maxoff;
	Page		page = BufferGetPage(buf);
	HashPageOpaque pageopaque;
	HashMetaPage metap;

	/* Scan each tuple in page to see if it is marked as LP_DEAD */
	maxoff = PageGetMaxOffsetNumber(page);
	for (offnum = FirstOffsetNumber;
		 offnum <= maxoff;
		 offnum = OffsetNumberNext(offnum))
	{
		ItemId		itemId = PageGetItemId(page, offnum);

		if (ItemIdIsDead(itemId))
			deletable[ndeletable++] = offnum;
	}

	if (ndeletable > 0)
	{
		TransactionId latestRemovedXid;

		latestRemovedXid =
			index_compute_xid_horizon_for_tuples(rel, hrel, buf,
												 deletable, ndeletable);

		/*
		 * Write-lock the meta page so that we can decrement tuple count.
		 */
		LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);

		/* No ereport(ERROR) until changes are logged */
		START_CRIT_SECTION();

		PageIndexMultiDelete(page, deletable, ndeletable);

		/*
		 * Mark the page as not containing any LP_DEAD items. This is not
		 * certainly true (there might be some that have recently been marked,
		 * but weren't included in our target-item list), but it will almost
		 * always be true and it doesn't seem worth an additional page scan to
		 * check it. Remember that LH_PAGE_HAS_DEAD_TUPLES is only a hint
		 * anyway.
		 */
		pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
		pageopaque->hasho_flag &= ~LH_PAGE_HAS_DEAD_TUPLES;

		metap = HashPageGetMeta(BufferGetPage(metabuf));
		metap->hashm_ntuples -= ndeletable;

		MarkBufferDirty(buf);
		MarkBufferDirty(metabuf);

		/* XLOG stuff */
		if (RelationNeedsWAL(rel))
		{
			xl_hash_vacuum_one_page xlrec;
			XLogRecPtr	recptr;

			xlrec.latestRemovedXid = latestRemovedXid;
			xlrec.ntuples = ndeletable;

			XLogBeginInsert();
			XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
			XLogRegisterData((char *) &xlrec, SizeOfHashVacuumOnePage);

			/*
			 * We need the target-offsets array whether or not we store the
			 * whole buffer, to allow us to find the latestRemovedXid on a
			 * standby server.
			 */
			XLogRegisterData((char *) deletable,
							 ndeletable * sizeof(OffsetNumber));

			XLogRegisterBuffer(1, metabuf, REGBUF_STANDARD);

			recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_VACUUM_ONE_PAGE);

			PageSetLSN(BufferGetPage(buf), recptr);
			PageSetLSN(BufferGetPage(metabuf), recptr);
		}

		END_CRIT_SECTION();

		/*
		 * Releasing write lock on meta page as we have updated the tuple
		 * count.
		 */
		LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);
	}
}