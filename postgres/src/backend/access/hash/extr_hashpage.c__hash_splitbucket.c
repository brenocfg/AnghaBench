#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  new_bucket_flag; int /*<<< orphan*/  old_bucket_flag; } ;
typedef  TYPE_1__ xl_hash_split_complete ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_12__ {int /*<<< orphan*/  hasho_flag; int /*<<< orphan*/  hasho_nextblkno; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_info; int /*<<< orphan*/  t_tid; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_2__* IndexTuple ;
typedef  TYPE_3__* HashPageOpaque ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 TYPE_2__* CopyIndexTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_READ ; 
 int /*<<< orphan*/  INDEX_MOVED_BY_SPLIT_MASK ; 
 scalar_t__ IndexTupleSize (TYPE_2__*) ; 
 scalar_t__ IsBufferCleanupOK (scalar_t__) ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LH_BUCKET_BEING_POPULATED ; 
 int /*<<< orphan*/  LH_BUCKET_BEING_SPLIT ; 
 int /*<<< orphan*/  LH_BUCKET_NEEDS_SPLIT_CLEANUP ; 
 int /*<<< orphan*/  LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetFreeSpaceForMultipleTuples (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPageSplit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHashSplitComplete ; 
 int /*<<< orphan*/  XLOG_HASH_SPLIT_COMPLETE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_addovflpage (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  _hash_get_indextuple_hashkey (TYPE_2__*) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_hashkey2bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_pgaddmultitup (int /*<<< orphan*/ ,scalar_t__,TYPE_2__**,scalar_t__*,int) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hashbucketcleanup (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_split_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
_hash_splitbucket(Relation rel,
				  Buffer metabuf,
				  Bucket obucket,
				  Bucket nbucket,
				  Buffer obuf,
				  Buffer nbuf,
				  HTAB *htab,
				  uint32 maxbucket,
				  uint32 highmask,
				  uint32 lowmask)
{
	Buffer		bucket_obuf;
	Buffer		bucket_nbuf;
	Page		opage;
	Page		npage;
	HashPageOpaque oopaque;
	HashPageOpaque nopaque;
	OffsetNumber itup_offsets[MaxIndexTuplesPerPage];
	IndexTuple	itups[MaxIndexTuplesPerPage];
	Size		all_tups_size = 0;
	int			i;
	uint16		nitups = 0;

	bucket_obuf = obuf;
	opage = BufferGetPage(obuf);
	oopaque = (HashPageOpaque) PageGetSpecialPointer(opage);

	bucket_nbuf = nbuf;
	npage = BufferGetPage(nbuf);
	nopaque = (HashPageOpaque) PageGetSpecialPointer(npage);

	/* Copy the predicate locks from old bucket to new bucket. */
	PredicateLockPageSplit(rel,
						   BufferGetBlockNumber(bucket_obuf),
						   BufferGetBlockNumber(bucket_nbuf));

	/*
	 * Partition the tuples in the old bucket between the old bucket and the
	 * new bucket, advancing along the old bucket's overflow bucket chain and
	 * adding overflow pages to the new bucket as needed.  Outer loop iterates
	 * once per page in old bucket.
	 */
	for (;;)
	{
		BlockNumber oblkno;
		OffsetNumber ooffnum;
		OffsetNumber omaxoffnum;

		/* Scan each tuple in old page */
		omaxoffnum = PageGetMaxOffsetNumber(opage);
		for (ooffnum = FirstOffsetNumber;
			 ooffnum <= omaxoffnum;
			 ooffnum = OffsetNumberNext(ooffnum))
		{
			IndexTuple	itup;
			Size		itemsz;
			Bucket		bucket;
			bool		found = false;

			/* skip dead tuples */
			if (ItemIdIsDead(PageGetItemId(opage, ooffnum)))
				continue;

			/*
			 * Before inserting a tuple, probe the hash table containing TIDs
			 * of tuples belonging to new bucket, if we find a match, then
			 * skip that tuple, else fetch the item's hash key (conveniently
			 * stored in the item) and determine which bucket it now belongs
			 * in.
			 */
			itup = (IndexTuple) PageGetItem(opage,
											PageGetItemId(opage, ooffnum));

			if (htab)
				(void) hash_search(htab, &itup->t_tid, HASH_FIND, &found);

			if (found)
				continue;

			bucket = _hash_hashkey2bucket(_hash_get_indextuple_hashkey(itup),
										  maxbucket, highmask, lowmask);

			if (bucket == nbucket)
			{
				IndexTuple	new_itup;

				/*
				 * make a copy of index tuple as we have to scribble on it.
				 */
				new_itup = CopyIndexTuple(itup);

				/*
				 * mark the index tuple as moved by split, such tuples are
				 * skipped by scan if there is split in progress for a bucket.
				 */
				new_itup->t_info |= INDEX_MOVED_BY_SPLIT_MASK;

				/*
				 * insert the tuple into the new bucket.  if it doesn't fit on
				 * the current page in the new bucket, we must allocate a new
				 * overflow page and place the tuple on that page instead.
				 */
				itemsz = IndexTupleSize(new_itup);
				itemsz = MAXALIGN(itemsz);

				if (PageGetFreeSpaceForMultipleTuples(npage, nitups + 1) < (all_tups_size + itemsz))
				{
					/*
					 * Change the shared buffer state in critical section,
					 * otherwise any error could make it unrecoverable.
					 */
					START_CRIT_SECTION();

					_hash_pgaddmultitup(rel, nbuf, itups, itup_offsets, nitups);
					MarkBufferDirty(nbuf);
					/* log the split operation before releasing the lock */
					log_split_page(rel, nbuf);

					END_CRIT_SECTION();

					/* drop lock, but keep pin */
					LockBuffer(nbuf, BUFFER_LOCK_UNLOCK);

					/* be tidy */
					for (i = 0; i < nitups; i++)
						pfree(itups[i]);
					nitups = 0;
					all_tups_size = 0;

					/* chain to a new overflow page */
					nbuf = _hash_addovflpage(rel, metabuf, nbuf, (nbuf == bucket_nbuf) ? true : false);
					npage = BufferGetPage(nbuf);
					nopaque = (HashPageOpaque) PageGetSpecialPointer(npage);
				}

				itups[nitups++] = new_itup;
				all_tups_size += itemsz;
			}
			else
			{
				/*
				 * the tuple stays on this page, so nothing to do.
				 */
				Assert(bucket == obucket);
			}
		}

		oblkno = oopaque->hasho_nextblkno;

		/* retain the pin on the old primary bucket */
		if (obuf == bucket_obuf)
			LockBuffer(obuf, BUFFER_LOCK_UNLOCK);
		else
			_hash_relbuf(rel, obuf);

		/* Exit loop if no more overflow pages in old bucket */
		if (!BlockNumberIsValid(oblkno))
		{
			/*
			 * Change the shared buffer state in critical section, otherwise
			 * any error could make it unrecoverable.
			 */
			START_CRIT_SECTION();

			_hash_pgaddmultitup(rel, nbuf, itups, itup_offsets, nitups);
			MarkBufferDirty(nbuf);
			/* log the split operation before releasing the lock */
			log_split_page(rel, nbuf);

			END_CRIT_SECTION();

			if (nbuf == bucket_nbuf)
				LockBuffer(nbuf, BUFFER_LOCK_UNLOCK);
			else
				_hash_relbuf(rel, nbuf);

			/* be tidy */
			for (i = 0; i < nitups; i++)
				pfree(itups[i]);
			break;
		}

		/* Else, advance to next old page */
		obuf = _hash_getbuf(rel, oblkno, HASH_READ, LH_OVERFLOW_PAGE);
		opage = BufferGetPage(obuf);
		oopaque = (HashPageOpaque) PageGetSpecialPointer(opage);
	}

	/*
	 * We're at the end of the old bucket chain, so we're done partitioning
	 * the tuples.  Mark the old and new buckets to indicate split is
	 * finished.
	 *
	 * To avoid deadlocks due to locking order of buckets, first lock the old
	 * bucket and then the new bucket.
	 */
	LockBuffer(bucket_obuf, BUFFER_LOCK_EXCLUSIVE);
	opage = BufferGetPage(bucket_obuf);
	oopaque = (HashPageOpaque) PageGetSpecialPointer(opage);

	LockBuffer(bucket_nbuf, BUFFER_LOCK_EXCLUSIVE);
	npage = BufferGetPage(bucket_nbuf);
	nopaque = (HashPageOpaque) PageGetSpecialPointer(npage);

	START_CRIT_SECTION();

	oopaque->hasho_flag &= ~LH_BUCKET_BEING_SPLIT;
	nopaque->hasho_flag &= ~LH_BUCKET_BEING_POPULATED;

	/*
	 * After the split is finished, mark the old bucket to indicate that it
	 * contains deletable tuples.  We will clear split-cleanup flag after
	 * deleting such tuples either at the end of split or at the next split
	 * from old bucket or at the time of vacuum.
	 */
	oopaque->hasho_flag |= LH_BUCKET_NEEDS_SPLIT_CLEANUP;

	/*
	 * now write the buffers, here we don't release the locks as caller is
	 * responsible to release locks.
	 */
	MarkBufferDirty(bucket_obuf);
	MarkBufferDirty(bucket_nbuf);

	if (RelationNeedsWAL(rel))
	{
		XLogRecPtr	recptr;
		xl_hash_split_complete xlrec;

		xlrec.old_bucket_flag = oopaque->hasho_flag;
		xlrec.new_bucket_flag = nopaque->hasho_flag;

		XLogBeginInsert();

		XLogRegisterData((char *) &xlrec, SizeOfHashSplitComplete);

		XLogRegisterBuffer(0, bucket_obuf, REGBUF_STANDARD);
		XLogRegisterBuffer(1, bucket_nbuf, REGBUF_STANDARD);

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_SPLIT_COMPLETE);

		PageSetLSN(BufferGetPage(bucket_obuf), recptr);
		PageSetLSN(BufferGetPage(bucket_nbuf), recptr);
	}

	END_CRIT_SECTION();

	/*
	 * If possible, clean up the old bucket.  We might not be able to do this
	 * if someone else has a pin on it, but if not then we can go ahead.  This
	 * isn't absolutely necessary, but it reduces bloat; if we don't do it
	 * now, VACUUM will do it eventually, but maybe not until new overflow
	 * pages have been allocated.  Note that there's no need to clean up the
	 * new bucket.
	 */
	if (IsBufferCleanupOK(bucket_obuf))
	{
		LockBuffer(bucket_nbuf, BUFFER_LOCK_UNLOCK);
		hashbucketcleanup(rel, obucket, bucket_obuf,
						  BufferGetBlockNumber(bucket_obuf), NULL,
						  maxbucket, highmask, lowmask, NULL, NULL, true,
						  NULL, NULL);
	}
	else
	{
		LockBuffer(bucket_nbuf, BUFFER_LOCK_UNLOCK);
		LockBuffer(bucket_obuf, BUFFER_LOCK_UNLOCK);
	}
}