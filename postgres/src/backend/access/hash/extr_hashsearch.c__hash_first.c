#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_28__ {scalar_t__ hasho_bucket; int /*<<< orphan*/  hasho_nextblkno; } ;
struct TYPE_22__ {size_t itemIndex; TYPE_5__* items; void* buf; } ;
struct TYPE_27__ {int hashso_buc_populated; TYPE_1__ currPos; int /*<<< orphan*/  hashso_buc_split; void* hashso_split_bucket_buf; void* hashso_bucket_buf; int /*<<< orphan*/  hashso_sk_hash; } ;
struct TYPE_26__ {int /*<<< orphan*/  heapTid; } ;
struct TYPE_25__ {int numberOfKeys; int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  xs_snapshot; TYPE_2__* keyData; int /*<<< orphan*/  opaque; TYPE_3__* indexRelation; } ;
struct TYPE_24__ {scalar_t__* rd_opcintype; } ;
struct TYPE_23__ {int sk_attno; scalar_t__ sk_strategy; int sk_flags; scalar_t__ sk_subtype; int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_2__* ScanKey ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_4__* IndexScanDesc ;
typedef  TYPE_5__ HashScanPosItem ;
typedef  TYPE_6__* HashScanOpaque ;
typedef  TYPE_7__* HashPageOpaque ;
typedef  void* Buffer ;
typedef  scalar_t__ Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (void*) ; 
 int /*<<< orphan*/  BufferGetPage (void*) ; 
 int BufferIsInvalid (void*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_READ ; 
 scalar_t__ HTEqualStrategyNumber ; 
 scalar_t__ H_BUCKET_BEING_POPULATED (TYPE_7__*) ; 
 void* InvalidBuffer ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LH_BUCKET_PAGE ; 
 int /*<<< orphan*/  LockBuffer (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SK_ISNULL ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_datum2hashkey (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_datum2hashkey_type (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_dropbuf (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  _hash_get_oldblock_from_newbucket (TYPE_3__*,scalar_t__) ; 
 void* _hash_getbucketbuf_from_hashkey (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* _hash_getbuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_readnext (TYPE_4__*,void**,int /*<<< orphan*/ *,TYPE_7__**) ; 
 int /*<<< orphan*/  _hash_readpage (TYPE_4__*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pgstat_count_index_scan (TYPE_3__*) ; 

bool
_hash_first(IndexScanDesc scan, ScanDirection dir)
{
	Relation	rel = scan->indexRelation;
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	ScanKey		cur;
	uint32		hashkey;
	Bucket		bucket;
	Buffer		buf;
	Page		page;
	HashPageOpaque opaque;
	HashScanPosItem *currItem;

	pgstat_count_index_scan(rel);

	/*
	 * We do not support hash scans with no index qualification, because we
	 * would have to read the whole index rather than just one bucket. That
	 * creates a whole raft of problems, since we haven't got a practical way
	 * to lock all the buckets against splits or compactions.
	 */
	if (scan->numberOfKeys < 1)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("hash indexes do not support whole-index scans")));

	/* There may be more than one index qual, but we hash only the first */
	cur = &scan->keyData[0];

	/* We support only single-column hash indexes */
	Assert(cur->sk_attno == 1);
	/* And there's only one operator strategy, too */
	Assert(cur->sk_strategy == HTEqualStrategyNumber);

	/*
	 * If the constant in the index qual is NULL, assume it cannot match any
	 * items in the index.
	 */
	if (cur->sk_flags & SK_ISNULL)
		return false;

	/*
	 * Okay to compute the hash key.  We want to do this before acquiring any
	 * locks, in case a user-defined hash function happens to be slow.
	 *
	 * If scankey operator is not a cross-type comparison, we can use the
	 * cached hash function; otherwise gotta look it up in the catalogs.
	 *
	 * We support the convention that sk_subtype == InvalidOid means the
	 * opclass input type; this is a hack to simplify life for ScanKeyInit().
	 */
	if (cur->sk_subtype == rel->rd_opcintype[0] ||
		cur->sk_subtype == InvalidOid)
		hashkey = _hash_datum2hashkey(rel, cur->sk_argument);
	else
		hashkey = _hash_datum2hashkey_type(rel, cur->sk_argument,
										   cur->sk_subtype);

	so->hashso_sk_hash = hashkey;

	buf = _hash_getbucketbuf_from_hashkey(rel, hashkey, HASH_READ, NULL);
	PredicateLockPage(rel, BufferGetBlockNumber(buf), scan->xs_snapshot);
	page = BufferGetPage(buf);
	TestForOldSnapshot(scan->xs_snapshot, rel, page);
	opaque = (HashPageOpaque) PageGetSpecialPointer(page);
	bucket = opaque->hasho_bucket;

	so->hashso_bucket_buf = buf;

	/*
	 * If a bucket split is in progress, then while scanning the bucket being
	 * populated, we need to skip tuples that were copied from bucket being
	 * split.  We also need to maintain a pin on the bucket being split to
	 * ensure that split-cleanup work done by vacuum doesn't remove tuples
	 * from it till this scan is done.  We need to maintain a pin on the
	 * bucket being populated to ensure that vacuum doesn't squeeze that
	 * bucket till this scan is complete; otherwise, the ordering of tuples
	 * can't be maintained during forward and backward scans.  Here, we have
	 * to be cautious about locking order: first, acquire the lock on bucket
	 * being split; then, release the lock on it but not the pin; then,
	 * acquire a lock on bucket being populated and again re-verify whether
	 * the bucket split is still in progress.  Acquiring the lock on bucket
	 * being split first ensures that the vacuum waits for this scan to
	 * finish.
	 */
	if (H_BUCKET_BEING_POPULATED(opaque))
	{
		BlockNumber old_blkno;
		Buffer		old_buf;

		old_blkno = _hash_get_oldblock_from_newbucket(rel, bucket);

		/*
		 * release the lock on new bucket and re-acquire it after acquiring
		 * the lock on old bucket.
		 */
		LockBuffer(buf, BUFFER_LOCK_UNLOCK);

		old_buf = _hash_getbuf(rel, old_blkno, HASH_READ, LH_BUCKET_PAGE);
		TestForOldSnapshot(scan->xs_snapshot, rel, BufferGetPage(old_buf));

		/*
		 * remember the split bucket buffer so as to use it later for
		 * scanning.
		 */
		so->hashso_split_bucket_buf = old_buf;
		LockBuffer(old_buf, BUFFER_LOCK_UNLOCK);

		LockBuffer(buf, BUFFER_LOCK_SHARE);
		page = BufferGetPage(buf);
		opaque = (HashPageOpaque) PageGetSpecialPointer(page);
		Assert(opaque->hasho_bucket == bucket);

		if (H_BUCKET_BEING_POPULATED(opaque))
			so->hashso_buc_populated = true;
		else
		{
			_hash_dropbuf(rel, so->hashso_split_bucket_buf);
			so->hashso_split_bucket_buf = InvalidBuffer;
		}
	}

	/* If a backwards scan is requested, move to the end of the chain */
	if (ScanDirectionIsBackward(dir))
	{
		/*
		 * Backward scans that start during split needs to start from end of
		 * bucket being split.
		 */
		while (BlockNumberIsValid(opaque->hasho_nextblkno) ||
			   (so->hashso_buc_populated && !so->hashso_buc_split))
			_hash_readnext(scan, &buf, &page, &opaque);
	}

	/* remember which buffer we have pinned, if any */
	Assert(BufferIsInvalid(so->currPos.buf));
	so->currPos.buf = buf;

	/* Now find all the tuples satisfying the qualification from a page */
	if (!_hash_readpage(scan, &buf, dir))
		return false;

	/* OK, itemIndex says what to return */
	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;

	/* if we're here, _hash_readpage found a valid tuples */
	return true;
}