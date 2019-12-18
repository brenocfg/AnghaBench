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
struct TYPE_8__ {int /*<<< orphan*/  offnum; } ;
typedef  TYPE_1__ xl_hash_insert ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int hashm_maxbucket; int hashm_ntuples; scalar_t__ hashm_ffactor; int /*<<< orphan*/  hashm_lowmask; int /*<<< orphan*/  hashm_highmask; } ;
struct TYPE_9__ {scalar_t__ hasho_bucket; int hasho_flag; int /*<<< orphan*/  hasho_nextblkno; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  TYPE_3__* HashMetaPage ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ Bucket ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_METAPAGE ; 
 int /*<<< orphan*/  HASH_NOLOCK ; 
 int /*<<< orphan*/  HASH_WRITE ; 
 scalar_t__ H_BUCKET_BEING_SPLIT (TYPE_2__*) ; 
 scalar_t__ H_HAS_DEAD_TUPLES (TYPE_2__*) ; 
 scalar_t__ HashMaxItemSize (int /*<<< orphan*/ ) ; 
 TYPE_3__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ IsBufferCleanupOK (scalar_t__) ; 
 int LH_META_PAGE ; 
 int LH_OVERFLOW_PAGE ; 
 int LH_PAGE_TYPE ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 scalar_t__ PageGetFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHashInsert ; 
 int /*<<< orphan*/  XLOG_HASH_INSERT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_addovflpage (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_expandtable (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_finish_split (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_get_indextuple_hashkey (scalar_t__) ; 
 scalar_t__ _hash_getbucketbuf_from_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_pgaddtup (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_vacuum_one_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__) ; 

void
_hash_doinsert(Relation rel, IndexTuple itup, Relation heapRel)
{
	Buffer		buf = InvalidBuffer;
	Buffer		bucket_buf;
	Buffer		metabuf;
	HashMetaPage metap;
	HashMetaPage usedmetap = NULL;
	Page		metapage;
	Page		page;
	HashPageOpaque pageopaque;
	Size		itemsz;
	bool		do_expand;
	uint32		hashkey;
	Bucket		bucket;
	OffsetNumber itup_off;

	/*
	 * Get the hash key for the item (it's stored in the index tuple itself).
	 */
	hashkey = _hash_get_indextuple_hashkey(itup);

	/* compute item size too */
	itemsz = IndexTupleSize(itup);
	itemsz = MAXALIGN(itemsz);	/* be safe, PageAddItem will do this but we
								 * need to be consistent */

restart_insert:

	/*
	 * Read the metapage.  We don't lock it yet; HashMaxItemSize() will
	 * examine pd_pagesize_version, but that can't change so we can examine it
	 * without a lock.
	 */
	metabuf = _hash_getbuf(rel, HASH_METAPAGE, HASH_NOLOCK, LH_META_PAGE);
	metapage = BufferGetPage(metabuf);

	/*
	 * Check whether the item can fit on a hash page at all. (Eventually, we
	 * ought to try to apply TOAST methods if not.)  Note that at this point,
	 * itemsz doesn't include the ItemId.
	 *
	 * XXX this is useless code if we are only storing hash keys.
	 */
	if (itemsz > HashMaxItemSize(metapage))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("index row size %zu exceeds hash maximum %zu",
						itemsz, HashMaxItemSize(metapage)),
				 errhint("Values larger than a buffer page cannot be indexed.")));

	/* Lock the primary bucket page for the target bucket. */
	buf = _hash_getbucketbuf_from_hashkey(rel, hashkey, HASH_WRITE,
										  &usedmetap);
	Assert(usedmetap != NULL);

	CheckForSerializableConflictIn(rel, NULL, buf);

	/* remember the primary bucket buffer to release the pin on it at end. */
	bucket_buf = buf;

	page = BufferGetPage(buf);
	pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
	bucket = pageopaque->hasho_bucket;

	/*
	 * If this bucket is in the process of being split, try to finish the
	 * split before inserting, because that might create room for the
	 * insertion to proceed without allocating an additional overflow page.
	 * It's only interesting to finish the split if we're trying to insert
	 * into the bucket from which we're removing tuples (the "old" bucket),
	 * not if we're trying to insert into the bucket into which tuples are
	 * being moved (the "new" bucket).
	 */
	if (H_BUCKET_BEING_SPLIT(pageopaque) && IsBufferCleanupOK(buf))
	{
		/* release the lock on bucket buffer, before completing the split. */
		LockBuffer(buf, BUFFER_LOCK_UNLOCK);

		_hash_finish_split(rel, metabuf, buf, bucket,
						   usedmetap->hashm_maxbucket,
						   usedmetap->hashm_highmask,
						   usedmetap->hashm_lowmask);

		/* release the pin on old and meta buffer.  retry for insert. */
		_hash_dropbuf(rel, buf);
		_hash_dropbuf(rel, metabuf);
		goto restart_insert;
	}

	/* Do the insertion */
	while (PageGetFreeSpace(page) < itemsz)
	{
		BlockNumber nextblkno;

		/*
		 * Check if current page has any DEAD tuples. If yes, delete these
		 * tuples and see if we can get a space for the new item to be
		 * inserted before moving to the next page in the bucket chain.
		 */
		if (H_HAS_DEAD_TUPLES(pageopaque))
		{

			if (IsBufferCleanupOK(buf))
			{
				_hash_vacuum_one_page(rel, heapRel, metabuf, buf);

				if (PageGetFreeSpace(page) >= itemsz)
					break;		/* OK, now we have enough space */
			}
		}

		/*
		 * no space on this page; check for an overflow page
		 */
		nextblkno = pageopaque->hasho_nextblkno;

		if (BlockNumberIsValid(nextblkno))
		{
			/*
			 * ovfl page exists; go get it.  if it doesn't have room, we'll
			 * find out next pass through the loop test above.  we always
			 * release both the lock and pin if this is an overflow page, but
			 * only the lock if this is the primary bucket page, since the pin
			 * on the primary bucket must be retained throughout the scan.
			 */
			if (buf != bucket_buf)
				_hash_relbuf(rel, buf);
			else
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
			buf = _hash_getbuf(rel, nextblkno, HASH_WRITE, LH_OVERFLOW_PAGE);
			page = BufferGetPage(buf);
		}
		else
		{
			/*
			 * we're at the end of the bucket chain and we haven't found a
			 * page with enough room.  allocate a new overflow page.
			 */

			/* release our write lock without modifying buffer */
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);

			/* chain to a new overflow page */
			buf = _hash_addovflpage(rel, metabuf, buf, (buf == bucket_buf) ? true : false);
			page = BufferGetPage(buf);

			/* should fit now, given test above */
			Assert(PageGetFreeSpace(page) >= itemsz);
		}
		pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
		Assert((pageopaque->hasho_flag & LH_PAGE_TYPE) == LH_OVERFLOW_PAGE);
		Assert(pageopaque->hasho_bucket == bucket);
	}

	/*
	 * Write-lock the metapage so we can increment the tuple count. After
	 * incrementing it, check to see if it's time for a split.
	 */
	LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);

	/* Do the update.  No ereport(ERROR) until changes are logged */
	START_CRIT_SECTION();

	/* found page with enough space, so add the item here */
	itup_off = _hash_pgaddtup(rel, buf, itemsz, itup);
	MarkBufferDirty(buf);

	/* metapage operations */
	metap = HashPageGetMeta(metapage);
	metap->hashm_ntuples += 1;

	/* Make sure this stays in sync with _hash_expandtable() */
	do_expand = metap->hashm_ntuples >
		(double) metap->hashm_ffactor * (metap->hashm_maxbucket + 1);

	MarkBufferDirty(metabuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_hash_insert xlrec;
		XLogRecPtr	recptr;

		xlrec.offnum = itup_off;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHashInsert);

		XLogRegisterBuffer(1, metabuf, REGBUF_STANDARD);

		XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
		XLogRegisterBufData(0, (char *) itup, IndexTupleSize(itup));

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_INSERT);

		PageSetLSN(BufferGetPage(buf), recptr);
		PageSetLSN(BufferGetPage(metabuf), recptr);
	}

	END_CRIT_SECTION();

	/* drop lock on metapage, but keep pin */
	LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);

	/*
	 * Release the modified page and ensure to release the pin on primary
	 * page.
	 */
	_hash_relbuf(rel, buf);
	if (buf != bucket_buf)
		_hash_dropbuf(rel, bucket_buf);

	/* Attempt to split if a split is needed */
	if (do_expand)
		_hash_expandtable(rel, metabuf);

	/* Finally drop our pin on the metapage */
	_hash_dropbuf(rel, metabuf);
}