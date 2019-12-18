#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {double ntuples; } ;
typedef  TYPE_1__ xl_hash_update_meta_page ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_18__ {scalar_t__ hashm_maxbucket; double hashm_ntuples; int /*<<< orphan*/  hashm_lowmask; int /*<<< orphan*/  hashm_highmask; } ;
struct TYPE_17__ {scalar_t__ hasho_prevblkno; } ;
struct TYPE_16__ {int estimated_count; double num_index_tuples; double tuples_removed; } ;
struct TYPE_15__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__ IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  TYPE_4__* HashPageOpaque ;
typedef  TYPE_5__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUCKET_TO_BLKNO (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  HASH_METAPAGE ; 
 int /*<<< orphan*/  HASH_NOLOCK ; 
 int /*<<< orphan*/  H_BUCKET_BEING_SPLIT (TYPE_4__*) ; 
 scalar_t__ H_NEEDS_SPLIT_CLEANUP (TYPE_4__*) ; 
 TYPE_5__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LH_BUCKET_PAGE ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHashUpdateMetaPage ; 
 int /*<<< orphan*/  XLOG_HASH_UPDATE_META_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* _hash_getcachedmetap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashbucketcleanup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*,int,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ palloc0 (int) ; 

IndexBulkDeleteResult *
hashbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			   IndexBulkDeleteCallback callback, void *callback_state)
{
	Relation	rel = info->index;
	double		tuples_removed;
	double		num_index_tuples;
	double		orig_ntuples;
	Bucket		orig_maxbucket;
	Bucket		cur_maxbucket;
	Bucket		cur_bucket;
	Buffer		metabuf = InvalidBuffer;
	HashMetaPage metap;
	HashMetaPage cachedmetap;

	tuples_removed = 0;
	num_index_tuples = 0;

	/*
	 * We need a copy of the metapage so that we can use its hashm_spares[]
	 * values to compute bucket page addresses, but a cached copy should be
	 * good enough.  (If not, we'll detect that further down and refresh the
	 * cache as necessary.)
	 */
	cachedmetap = _hash_getcachedmetap(rel, &metabuf, false);
	Assert(cachedmetap != NULL);

	orig_maxbucket = cachedmetap->hashm_maxbucket;
	orig_ntuples = cachedmetap->hashm_ntuples;

	/* Scan the buckets that we know exist */
	cur_bucket = 0;
	cur_maxbucket = orig_maxbucket;

loop_top:
	while (cur_bucket <= cur_maxbucket)
	{
		BlockNumber bucket_blkno;
		BlockNumber blkno;
		Buffer		bucket_buf;
		Buffer		buf;
		HashPageOpaque bucket_opaque;
		Page		page;
		bool		split_cleanup = false;

		/* Get address of bucket's start page */
		bucket_blkno = BUCKET_TO_BLKNO(cachedmetap, cur_bucket);

		blkno = bucket_blkno;

		/*
		 * We need to acquire a cleanup lock on the primary bucket page to out
		 * wait concurrent scans before deleting the dead tuples.
		 */
		buf = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL, info->strategy);
		LockBufferForCleanup(buf);
		_hash_checkpage(rel, buf, LH_BUCKET_PAGE);

		page = BufferGetPage(buf);
		bucket_opaque = (HashPageOpaque) PageGetSpecialPointer(page);

		/*
		 * If the bucket contains tuples that are moved by split, then we need
		 * to delete such tuples.  We can't delete such tuples if the split
		 * operation on bucket is not finished as those are needed by scans.
		 */
		if (!H_BUCKET_BEING_SPLIT(bucket_opaque) &&
			H_NEEDS_SPLIT_CLEANUP(bucket_opaque))
		{
			split_cleanup = true;

			/*
			 * This bucket might have been split since we last held a lock on
			 * the metapage.  If so, hashm_maxbucket, hashm_highmask and
			 * hashm_lowmask might be old enough to cause us to fail to remove
			 * tuples left behind by the most recent split.  To prevent that,
			 * now that the primary page of the target bucket has been locked
			 * (and thus can't be further split), check whether we need to
			 * update our cached metapage data.
			 */
			Assert(bucket_opaque->hasho_prevblkno != InvalidBlockNumber);
			if (bucket_opaque->hasho_prevblkno > cachedmetap->hashm_maxbucket)
			{
				cachedmetap = _hash_getcachedmetap(rel, &metabuf, true);
				Assert(cachedmetap != NULL);
			}
		}

		bucket_buf = buf;

		hashbucketcleanup(rel, cur_bucket, bucket_buf, blkno, info->strategy,
						  cachedmetap->hashm_maxbucket,
						  cachedmetap->hashm_highmask,
						  cachedmetap->hashm_lowmask, &tuples_removed,
						  &num_index_tuples, split_cleanup,
						  callback, callback_state);

		_hash_dropbuf(rel, bucket_buf);

		/* Advance to next bucket */
		cur_bucket++;
	}

	if (BufferIsInvalid(metabuf))
		metabuf = _hash_getbuf(rel, HASH_METAPAGE, HASH_NOLOCK, LH_META_PAGE);

	/* Write-lock metapage and check for split since we started */
	LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);
	metap = HashPageGetMeta(BufferGetPage(metabuf));

	if (cur_maxbucket != metap->hashm_maxbucket)
	{
		/* There's been a split, so process the additional bucket(s) */
		LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);
		cachedmetap = _hash_getcachedmetap(rel, &metabuf, true);
		Assert(cachedmetap != NULL);
		cur_maxbucket = cachedmetap->hashm_maxbucket;
		goto loop_top;
	}

	/* Okay, we're really done.  Update tuple count in metapage. */
	START_CRIT_SECTION();

	if (orig_maxbucket == metap->hashm_maxbucket &&
		orig_ntuples == metap->hashm_ntuples)
	{
		/*
		 * No one has split or inserted anything since start of scan, so
		 * believe our count as gospel.
		 */
		metap->hashm_ntuples = num_index_tuples;
	}
	else
	{
		/*
		 * Otherwise, our count is untrustworthy since we may have
		 * double-scanned tuples in split buckets.  Proceed by dead-reckoning.
		 * (Note: we still return estimated_count = false, because using this
		 * count is better than not updating reltuples at all.)
		 */
		if (metap->hashm_ntuples > tuples_removed)
			metap->hashm_ntuples -= tuples_removed;
		else
			metap->hashm_ntuples = 0;
		num_index_tuples = metap->hashm_ntuples;
	}

	MarkBufferDirty(metabuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_hash_update_meta_page xlrec;
		XLogRecPtr	recptr;

		xlrec.ntuples = metap->hashm_ntuples;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHashUpdateMetaPage);

		XLogRegisterBuffer(0, metabuf, REGBUF_STANDARD);

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_UPDATE_META_PAGE);
		PageSetLSN(BufferGetPage(metabuf), recptr);
	}

	END_CRIT_SECTION();

	_hash_relbuf(rel, metabuf);

	/* return statistics */
	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
	stats->estimated_count = false;
	stats->num_index_tuples = num_index_tuples;
	stats->tuples_removed += tuples_removed;
	/* hashvacuumcleanup will fill in num_pages */

	return stats;
}