#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ntups; int is_prim_bucket_same_wrt; } ;
typedef  TYPE_1__ xl_hash_move_page_contents ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_4__ {scalar_t__ hasho_nextblkno; scalar_t__ hasho_bucket; scalar_t__ hasho_prevblkno; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ Bucket ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int BlockNumberIsValid (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ CopyIndexTuple (scalar_t__) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  HASH_WRITE ; 
 scalar_t__ IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 int MaxIndexTuplesPerPage ; 
 int MaxOffsetNumber ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetFreeSpaceForMultipleTuples (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  PageIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_NO_IMAGE ; 
 int REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHashMovePageContents ; 
 int /*<<< orphan*/  XLOG_HASH_MOVE_PAGE_CONTENTS ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogEnsureRecordSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_freeovflpage (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_getbuf_with_strategy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_pgaddmultitup (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

void
_hash_squeezebucket(Relation rel,
					Bucket bucket,
					BlockNumber bucket_blkno,
					Buffer bucket_buf,
					BufferAccessStrategy bstrategy)
{
	BlockNumber wblkno;
	BlockNumber rblkno;
	Buffer		wbuf;
	Buffer		rbuf;
	Page		wpage;
	Page		rpage;
	HashPageOpaque wopaque;
	HashPageOpaque ropaque;

	/*
	 * start squeezing into the primary bucket page.
	 */
	wblkno = bucket_blkno;
	wbuf = bucket_buf;
	wpage = BufferGetPage(wbuf);
	wopaque = (HashPageOpaque) PageGetSpecialPointer(wpage);

	/*
	 * if there aren't any overflow pages, there's nothing to squeeze. caller
	 * is responsible for releasing the pin on primary bucket page.
	 */
	if (!BlockNumberIsValid(wopaque->hasho_nextblkno))
	{
		LockBuffer(wbuf, BUFFER_LOCK_UNLOCK);
		return;
	}

	/*
	 * Find the last page in the bucket chain by starting at the base bucket
	 * page and working forward.  Note: we assume that a hash bucket chain is
	 * usually smaller than the buffer ring being used by VACUUM, else using
	 * the access strategy here would be counterproductive.
	 */
	rbuf = InvalidBuffer;
	ropaque = wopaque;
	do
	{
		rblkno = ropaque->hasho_nextblkno;
		if (rbuf != InvalidBuffer)
			_hash_relbuf(rel, rbuf);
		rbuf = _hash_getbuf_with_strategy(rel,
										  rblkno,
										  HASH_WRITE,
										  LH_OVERFLOW_PAGE,
										  bstrategy);
		rpage = BufferGetPage(rbuf);
		ropaque = (HashPageOpaque) PageGetSpecialPointer(rpage);
		Assert(ropaque->hasho_bucket == bucket);
	} while (BlockNumberIsValid(ropaque->hasho_nextblkno));

	/*
	 * squeeze the tuples.
	 */
	for (;;)
	{
		OffsetNumber roffnum;
		OffsetNumber maxroffnum;
		OffsetNumber deletable[MaxOffsetNumber];
		IndexTuple	itups[MaxIndexTuplesPerPage];
		Size		tups_size[MaxIndexTuplesPerPage];
		OffsetNumber itup_offsets[MaxIndexTuplesPerPage];
		uint16		ndeletable = 0;
		uint16		nitups = 0;
		Size		all_tups_size = 0;
		int			i;
		bool		retain_pin = false;

readpage:
		/* Scan each tuple in "read" page */
		maxroffnum = PageGetMaxOffsetNumber(rpage);
		for (roffnum = FirstOffsetNumber;
			 roffnum <= maxroffnum;
			 roffnum = OffsetNumberNext(roffnum))
		{
			IndexTuple	itup;
			Size		itemsz;

			/* skip dead tuples */
			if (ItemIdIsDead(PageGetItemId(rpage, roffnum)))
				continue;

			itup = (IndexTuple) PageGetItem(rpage,
											PageGetItemId(rpage, roffnum));
			itemsz = IndexTupleSize(itup);
			itemsz = MAXALIGN(itemsz);

			/*
			 * Walk up the bucket chain, looking for a page big enough for
			 * this item and all other accumulated items.  Exit if we reach
			 * the read page.
			 */
			while (PageGetFreeSpaceForMultipleTuples(wpage, nitups + 1) < (all_tups_size + itemsz))
			{
				Buffer		next_wbuf = InvalidBuffer;
				bool		tups_moved = false;

				Assert(!PageIsEmpty(wpage));

				if (wblkno == bucket_blkno)
					retain_pin = true;

				wblkno = wopaque->hasho_nextblkno;
				Assert(BlockNumberIsValid(wblkno));

				/* don't need to move to next page if we reached the read page */
				if (wblkno != rblkno)
					next_wbuf = _hash_getbuf_with_strategy(rel,
														   wblkno,
														   HASH_WRITE,
														   LH_OVERFLOW_PAGE,
														   bstrategy);

				if (nitups > 0)
				{
					Assert(nitups == ndeletable);

					/*
					 * This operation needs to log multiple tuples, prepare
					 * WAL for that.
					 */
					if (RelationNeedsWAL(rel))
						XLogEnsureRecordSpace(0, 3 + nitups);

					START_CRIT_SECTION();

					/*
					 * we have to insert tuples on the "write" page, being
					 * careful to preserve hashkey ordering.  (If we insert
					 * many tuples into the same "write" page it would be
					 * worth qsort'ing them).
					 */
					_hash_pgaddmultitup(rel, wbuf, itups, itup_offsets, nitups);
					MarkBufferDirty(wbuf);

					/* Delete tuples we already moved off read page */
					PageIndexMultiDelete(rpage, deletable, ndeletable);
					MarkBufferDirty(rbuf);

					/* XLOG stuff */
					if (RelationNeedsWAL(rel))
					{
						XLogRecPtr	recptr;
						xl_hash_move_page_contents xlrec;

						xlrec.ntups = nitups;
						xlrec.is_prim_bucket_same_wrt = (wbuf == bucket_buf) ? true : false;

						XLogBeginInsert();
						XLogRegisterData((char *) &xlrec, SizeOfHashMovePageContents);

						/*
						 * bucket buffer needs to be registered to ensure that
						 * we can acquire a cleanup lock on it during replay.
						 */
						if (!xlrec.is_prim_bucket_same_wrt)
							XLogRegisterBuffer(0, bucket_buf, REGBUF_STANDARD | REGBUF_NO_IMAGE);

						XLogRegisterBuffer(1, wbuf, REGBUF_STANDARD);
						XLogRegisterBufData(1, (char *) itup_offsets,
											nitups * sizeof(OffsetNumber));
						for (i = 0; i < nitups; i++)
							XLogRegisterBufData(1, (char *) itups[i], tups_size[i]);

						XLogRegisterBuffer(2, rbuf, REGBUF_STANDARD);
						XLogRegisterBufData(2, (char *) deletable,
											ndeletable * sizeof(OffsetNumber));

						recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_MOVE_PAGE_CONTENTS);

						PageSetLSN(BufferGetPage(wbuf), recptr);
						PageSetLSN(BufferGetPage(rbuf), recptr);
					}

					END_CRIT_SECTION();

					tups_moved = true;
				}

				/*
				 * release the lock on previous page after acquiring the lock
				 * on next page
				 */
				if (retain_pin)
					LockBuffer(wbuf, BUFFER_LOCK_UNLOCK);
				else
					_hash_relbuf(rel, wbuf);

				/* nothing more to do if we reached the read page */
				if (rblkno == wblkno)
				{
					_hash_relbuf(rel, rbuf);
					return;
				}

				wbuf = next_wbuf;
				wpage = BufferGetPage(wbuf);
				wopaque = (HashPageOpaque) PageGetSpecialPointer(wpage);
				Assert(wopaque->hasho_bucket == bucket);
				retain_pin = false;

				/* be tidy */
				for (i = 0; i < nitups; i++)
					pfree(itups[i]);
				nitups = 0;
				all_tups_size = 0;
				ndeletable = 0;

				/*
				 * after moving the tuples, rpage would have been compacted,
				 * so we need to rescan it.
				 */
				if (tups_moved)
					goto readpage;
			}

			/* remember tuple for deletion from "read" page */
			deletable[ndeletable++] = roffnum;

			/*
			 * we need a copy of index tuples as they can be freed as part of
			 * overflow page, however we need them to write a WAL record in
			 * _hash_freeovflpage.
			 */
			itups[nitups] = CopyIndexTuple(itup);
			tups_size[nitups++] = itemsz;
			all_tups_size += itemsz;
		}

		/*
		 * If we reach here, there are no live tuples on the "read" page ---
		 * it was empty when we got to it, or we moved them all.  So we can
		 * just free the page without bothering with deleting tuples
		 * individually.  Then advance to the previous "read" page.
		 *
		 * Tricky point here: if our read and write pages are adjacent in the
		 * bucket chain, our write lock on wbuf will conflict with
		 * _hash_freeovflpage's attempt to update the sibling links of the
		 * removed page.  In that case, we don't need to lock it again.
		 */
		rblkno = ropaque->hasho_prevblkno;
		Assert(BlockNumberIsValid(rblkno));

		/* free this overflow page (releases rbuf) */
		_hash_freeovflpage(rel, bucket_buf, rbuf, wbuf, itups, itup_offsets,
						   tups_size, nitups, bstrategy);

		/* be tidy */
		for (i = 0; i < nitups; i++)
			pfree(itups[i]);

		/* are we freeing the page adjacent to wbuf? */
		if (rblkno == wblkno)
		{
			/* retain the pin on primary bucket page till end of bucket scan */
			if (wblkno == bucket_blkno)
				LockBuffer(wbuf, BUFFER_LOCK_UNLOCK);
			else
				_hash_relbuf(rel, wbuf);
			return;
		}

		rbuf = _hash_getbuf_with_strategy(rel,
										  rblkno,
										  HASH_WRITE,
										  LH_OVERFLOW_PAGE,
										  bstrategy);
		rpage = BufferGetPage(rbuf);
		ropaque = (HashPageOpaque) PageGetSpecialPointer(rpage);
		Assert(ropaque->hasho_bucket == bucket);
	}

	/* NOTREACHED */
}