#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int new_bucket; int old_bucket_flag; int new_bucket_flag; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ xl_hash_split_allocate_page ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {double hashm_ntuples; int hashm_maxbucket; int hashm_lowmask; int hashm_highmask; int hashm_ovflpoint; scalar_t__* hashm_spares; scalar_t__ hashm_ffactor; } ;
struct TYPE_9__ {int hasho_flag; int hasho_prevblkno; int hasho_bucket; int /*<<< orphan*/  hasho_page_id; int /*<<< orphan*/  hasho_nextblkno; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  TYPE_3__* HashMetaPage ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUCKET_TO_BLKNO (TYPE_3__*,int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  HASHO_PAGE_ID ; 
 scalar_t__ H_BUCKET_BEING_SPLIT (TYPE_2__*) ; 
 scalar_t__ H_NEEDS_SPLIT_CLEANUP (TYPE_2__*) ; 
 TYPE_3__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  IsBufferCleanupOK (int /*<<< orphan*/ ) ; 
 int LH_BUCKET_BEING_POPULATED ; 
 int LH_BUCKET_BEING_SPLIT ; 
 int LH_BUCKET_PAGE ; 
 int /*<<< orphan*/  LH_META_PAGE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHashSplitAllocPage ; 
 int /*<<< orphan*/  XLH_SPLIT_META_UPDATE_MASKS ; 
 int /*<<< orphan*/  XLH_SPLIT_META_UPDATE_SPLITPOINT ; 
 int /*<<< orphan*/  XLOG_HASH_SPLIT_ALLOCATE_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_alloc_buckets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_finish_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int _hash_get_totalbuckets (int) ; 
 int /*<<< orphan*/  _hash_getbuf_with_condlock_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_getnewbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _hash_spareindex (int) ; 
 int /*<<< orphan*/  _hash_splitbucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  hashbucketcleanup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
_hash_expandtable(Relation rel, Buffer metabuf)
{
	HashMetaPage metap;
	Bucket		old_bucket;
	Bucket		new_bucket;
	uint32		spare_ndx;
	BlockNumber start_oblkno;
	BlockNumber start_nblkno;
	Buffer		buf_nblkno;
	Buffer		buf_oblkno;
	Page		opage;
	Page		npage;
	HashPageOpaque oopaque;
	HashPageOpaque nopaque;
	uint32		maxbucket;
	uint32		highmask;
	uint32		lowmask;
	bool		metap_update_masks = false;
	bool		metap_update_splitpoint = false;

restart_expand:

	/*
	 * Write-lock the meta page.  It used to be necessary to acquire a
	 * heavyweight lock to begin a split, but that is no longer required.
	 */
	LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);

	_hash_checkpage(rel, metabuf, LH_META_PAGE);
	metap = HashPageGetMeta(BufferGetPage(metabuf));

	/*
	 * Check to see if split is still needed; someone else might have already
	 * done one while we waited for the lock.
	 *
	 * Make sure this stays in sync with _hash_doinsert()
	 */
	if (metap->hashm_ntuples <=
		(double) metap->hashm_ffactor * (metap->hashm_maxbucket + 1))
		goto fail;

	/*
	 * Can't split anymore if maxbucket has reached its maximum possible
	 * value.
	 *
	 * Ideally we'd allow bucket numbers up to UINT_MAX-1 (no higher because
	 * the calculation maxbucket+1 mustn't overflow).  Currently we restrict
	 * to half that because of overflow looping in _hash_log2() and
	 * insufficient space in hashm_spares[].  It's moot anyway because an
	 * index with 2^32 buckets would certainly overflow BlockNumber and hence
	 * _hash_alloc_buckets() would fail, but if we supported buckets smaller
	 * than a disk block then this would be an independent constraint.
	 *
	 * If you change this, see also the maximum initial number of buckets in
	 * _hash_init().
	 */
	if (metap->hashm_maxbucket >= (uint32) 0x7FFFFFFE)
		goto fail;

	/*
	 * Determine which bucket is to be split, and attempt to take cleanup lock
	 * on the old bucket.  If we can't get the lock, give up.
	 *
	 * The cleanup lock protects us not only against other backends, but
	 * against our own backend as well.
	 *
	 * The cleanup lock is mainly to protect the split from concurrent
	 * inserts. See src/backend/access/hash/README, Lock Definitions for
	 * further details.  Due to this locking restriction, if there is any
	 * pending scan, the split will give up which is not good, but harmless.
	 */
	new_bucket = metap->hashm_maxbucket + 1;

	old_bucket = (new_bucket & metap->hashm_lowmask);

	start_oblkno = BUCKET_TO_BLKNO(metap, old_bucket);

	buf_oblkno = _hash_getbuf_with_condlock_cleanup(rel, start_oblkno, LH_BUCKET_PAGE);
	if (!buf_oblkno)
		goto fail;

	opage = BufferGetPage(buf_oblkno);
	oopaque = (HashPageOpaque) PageGetSpecialPointer(opage);

	/*
	 * We want to finish the split from a bucket as there is no apparent
	 * benefit by not doing so and it will make the code complicated to finish
	 * the split that involves multiple buckets considering the case where new
	 * split also fails.  We don't need to consider the new bucket for
	 * completing the split here as it is not possible that a re-split of new
	 * bucket starts when there is still a pending split from old bucket.
	 */
	if (H_BUCKET_BEING_SPLIT(oopaque))
	{
		/*
		 * Copy bucket mapping info now; refer the comment in code below where
		 * we copy this information before calling _hash_splitbucket to see
		 * why this is okay.
		 */
		maxbucket = metap->hashm_maxbucket;
		highmask = metap->hashm_highmask;
		lowmask = metap->hashm_lowmask;

		/*
		 * Release the lock on metapage and old_bucket, before completing the
		 * split.
		 */
		LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);
		LockBuffer(buf_oblkno, BUFFER_LOCK_UNLOCK);

		_hash_finish_split(rel, metabuf, buf_oblkno, old_bucket, maxbucket,
						   highmask, lowmask);

		/* release the pin on old buffer and retry for expand. */
		_hash_dropbuf(rel, buf_oblkno);

		goto restart_expand;
	}

	/*
	 * Clean the tuples remained from the previous split.  This operation
	 * requires cleanup lock and we already have one on the old bucket, so
	 * let's do it. We also don't want to allow further splits from the bucket
	 * till the garbage of previous split is cleaned.  This has two
	 * advantages; first, it helps in avoiding the bloat due to garbage and
	 * second is, during cleanup of bucket, we are always sure that the
	 * garbage tuples belong to most recently split bucket.  On the contrary,
	 * if we allow cleanup of bucket after meta page is updated to indicate
	 * the new split and before the actual split, the cleanup operation won't
	 * be able to decide whether the tuple has been moved to the newly created
	 * bucket and ended up deleting such tuples.
	 */
	if (H_NEEDS_SPLIT_CLEANUP(oopaque))
	{
		/*
		 * Copy bucket mapping info now; refer to the comment in code below
		 * where we copy this information before calling _hash_splitbucket to
		 * see why this is okay.
		 */
		maxbucket = metap->hashm_maxbucket;
		highmask = metap->hashm_highmask;
		lowmask = metap->hashm_lowmask;

		/* Release the metapage lock. */
		LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);

		hashbucketcleanup(rel, old_bucket, buf_oblkno, start_oblkno, NULL,
						  maxbucket, highmask, lowmask, NULL, NULL, true,
						  NULL, NULL);

		_hash_dropbuf(rel, buf_oblkno);

		goto restart_expand;
	}

	/*
	 * There shouldn't be any active scan on new bucket.
	 *
	 * Note: it is safe to compute the new bucket's blkno here, even though we
	 * may still need to update the BUCKET_TO_BLKNO mapping.  This is because
	 * the current value of hashm_spares[hashm_ovflpoint] correctly shows
	 * where we are going to put a new splitpoint's worth of buckets.
	 */
	start_nblkno = BUCKET_TO_BLKNO(metap, new_bucket);

	/*
	 * If the split point is increasing we need to allocate a new batch of
	 * bucket pages.
	 */
	spare_ndx = _hash_spareindex(new_bucket + 1);
	if (spare_ndx > metap->hashm_ovflpoint)
	{
		uint32		buckets_to_add;

		Assert(spare_ndx == metap->hashm_ovflpoint + 1);

		/*
		 * We treat allocation of buckets as a separate WAL-logged action.
		 * Even if we fail after this operation, won't leak bucket pages;
		 * rather, the next split will consume this space. In any case, even
		 * without failure we don't use all the space in one split operation.
		 */
		buckets_to_add = _hash_get_totalbuckets(spare_ndx) - new_bucket;
		if (!_hash_alloc_buckets(rel, start_nblkno, buckets_to_add))
		{
			/* can't split due to BlockNumber overflow */
			_hash_relbuf(rel, buf_oblkno);
			goto fail;
		}
	}

	/*
	 * Physically allocate the new bucket's primary page.  We want to do this
	 * before changing the metapage's mapping info, in case we can't get the
	 * disk space.  Ideally, we don't need to check for cleanup lock on new
	 * bucket as no other backend could find this bucket unless meta page is
	 * updated.  However, it is good to be consistent with old bucket locking.
	 */
	buf_nblkno = _hash_getnewbuf(rel, start_nblkno, MAIN_FORKNUM);
	if (!IsBufferCleanupOK(buf_nblkno))
	{
		_hash_relbuf(rel, buf_oblkno);
		_hash_relbuf(rel, buf_nblkno);
		goto fail;
	}

	/*
	 * Since we are scribbling on the pages in the shared buffers, establish a
	 * critical section.  Any failure in this next code leaves us with a big
	 * problem: the metapage is effectively corrupt but could get written back
	 * to disk.
	 */
	START_CRIT_SECTION();

	/*
	 * Okay to proceed with split.  Update the metapage bucket mapping info.
	 */
	metap->hashm_maxbucket = new_bucket;

	if (new_bucket > metap->hashm_highmask)
	{
		/* Starting a new doubling */
		metap->hashm_lowmask = metap->hashm_highmask;
		metap->hashm_highmask = new_bucket | metap->hashm_lowmask;
		metap_update_masks = true;
	}

	/*
	 * If the split point is increasing we need to adjust the hashm_spares[]
	 * array and hashm_ovflpoint so that future overflow pages will be created
	 * beyond this new batch of bucket pages.
	 */
	if (spare_ndx > metap->hashm_ovflpoint)
	{
		metap->hashm_spares[spare_ndx] = metap->hashm_spares[metap->hashm_ovflpoint];
		metap->hashm_ovflpoint = spare_ndx;
		metap_update_splitpoint = true;
	}

	MarkBufferDirty(metabuf);

	/*
	 * Copy bucket mapping info now; this saves re-accessing the meta page
	 * inside _hash_splitbucket's inner loop.  Note that once we drop the
	 * split lock, other splits could begin, so these values might be out of
	 * date before _hash_splitbucket finishes.  That's okay, since all it
	 * needs is to tell which of these two buckets to map hashkeys into.
	 */
	maxbucket = metap->hashm_maxbucket;
	highmask = metap->hashm_highmask;
	lowmask = metap->hashm_lowmask;

	opage = BufferGetPage(buf_oblkno);
	oopaque = (HashPageOpaque) PageGetSpecialPointer(opage);

	/*
	 * Mark the old bucket to indicate that split is in progress.  (At
	 * operation end, we will clear the split-in-progress flag.)  Also, for a
	 * primary bucket page, hasho_prevblkno stores the number of buckets that
	 * existed as of the last split, so we must update that value here.
	 */
	oopaque->hasho_flag |= LH_BUCKET_BEING_SPLIT;
	oopaque->hasho_prevblkno = maxbucket;

	MarkBufferDirty(buf_oblkno);

	npage = BufferGetPage(buf_nblkno);

	/*
	 * initialize the new bucket's primary page and mark it to indicate that
	 * split is in progress.
	 */
	nopaque = (HashPageOpaque) PageGetSpecialPointer(npage);
	nopaque->hasho_prevblkno = maxbucket;
	nopaque->hasho_nextblkno = InvalidBlockNumber;
	nopaque->hasho_bucket = new_bucket;
	nopaque->hasho_flag = LH_BUCKET_PAGE | LH_BUCKET_BEING_POPULATED;
	nopaque->hasho_page_id = HASHO_PAGE_ID;

	MarkBufferDirty(buf_nblkno);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_hash_split_allocate_page xlrec;
		XLogRecPtr	recptr;

		xlrec.new_bucket = maxbucket;
		xlrec.old_bucket_flag = oopaque->hasho_flag;
		xlrec.new_bucket_flag = nopaque->hasho_flag;
		xlrec.flags = 0;

		XLogBeginInsert();

		XLogRegisterBuffer(0, buf_oblkno, REGBUF_STANDARD);
		XLogRegisterBuffer(1, buf_nblkno, REGBUF_WILL_INIT);
		XLogRegisterBuffer(2, metabuf, REGBUF_STANDARD);

		if (metap_update_masks)
		{
			xlrec.flags |= XLH_SPLIT_META_UPDATE_MASKS;
			XLogRegisterBufData(2, (char *) &metap->hashm_lowmask, sizeof(uint32));
			XLogRegisterBufData(2, (char *) &metap->hashm_highmask, sizeof(uint32));
		}

		if (metap_update_splitpoint)
		{
			xlrec.flags |= XLH_SPLIT_META_UPDATE_SPLITPOINT;
			XLogRegisterBufData(2, (char *) &metap->hashm_ovflpoint,
								sizeof(uint32));
			XLogRegisterBufData(2,
								(char *) &metap->hashm_spares[metap->hashm_ovflpoint],
								sizeof(uint32));
		}

		XLogRegisterData((char *) &xlrec, SizeOfHashSplitAllocPage);

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_SPLIT_ALLOCATE_PAGE);

		PageSetLSN(BufferGetPage(buf_oblkno), recptr);
		PageSetLSN(BufferGetPage(buf_nblkno), recptr);
		PageSetLSN(BufferGetPage(metabuf), recptr);
	}

	END_CRIT_SECTION();

	/* drop lock, but keep pin */
	LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);

	/* Relocate records to the new bucket */
	_hash_splitbucket(rel, metabuf,
					  old_bucket, new_bucket,
					  buf_oblkno, buf_nblkno, NULL,
					  maxbucket, highmask, lowmask);

	/* all done, now release the pins on primary buckets. */
	_hash_dropbuf(rel, buf_oblkno);
	_hash_dropbuf(rel, buf_nblkno);

	return;

	/* Here if decide not to split or fail to acquire old bucket lock */
fail:

	/* We didn't write the metapage, so just drop lock */
	LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);
}