#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {double num_tuples; int /*<<< orphan*/  ffactor; int /*<<< orphan*/  procid; } ;
typedef  TYPE_1__ xl_hash_init_meta_page ;
struct TYPE_16__ {int /*<<< orphan*/  bmsize; } ;
typedef  TYPE_2__ xl_hash_init_bitmap_page ;
typedef  scalar_t__ uint32 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_18__ {scalar_t__ hashm_maxbucket; size_t hashm_nmaps; int /*<<< orphan*/  hashm_bmsize; scalar_t__* hashm_mapp; int /*<<< orphan*/  hashm_ffactor; int /*<<< orphan*/  hashm_procid; } ;
struct TYPE_17__ {int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_4__* HashMetaPage ;
typedef  scalar_t__ ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BUCKET_TO_BLKNO (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASHSTANDARD_PROC ; 
 int /*<<< orphan*/  HASH_DEFAULT_FILLFACTOR ; 
 size_t HASH_MAX_BITMAPS ; 
 scalar_t__ HASH_METAPAGE ; 
 TYPE_4__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ INIT_FORKNUM ; 
 int /*<<< orphan*/  LH_BUCKET_PAGE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_HASH_ID ; 
 scalar_t__ RelationGetNumberOfBlocksInFork (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int RelationGetTargetPageUsage (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (TYPE_3__*) ; 
 int /*<<< orphan*/  SizeOfHashInitBitmapPage ; 
 int /*<<< orphan*/  SizeOfHashInitMetaPage ; 
 int /*<<< orphan*/  XLOG_HASH_INIT_BITMAP_PAGE ; 
 int /*<<< orphan*/  XLOG_HASH_INIT_META_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_getnewbuf (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _hash_init_metabuffer (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _hash_initbitmapbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_initbuf (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_relbuf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getprocid (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 

uint32
_hash_init(Relation rel, double num_tuples, ForkNumber forkNum)
{
	Buffer		metabuf;
	Buffer		buf;
	Buffer		bitmapbuf;
	Page		pg;
	HashMetaPage metap;
	RegProcedure procid;
	int32		data_width;
	int32		item_width;
	int32		ffactor;
	uint32		num_buckets;
	uint32		i;
	bool		use_wal;

	/* safety check */
	if (RelationGetNumberOfBlocksInFork(rel, forkNum) != 0)
		elog(ERROR, "cannot initialize non-empty hash index \"%s\"",
			 RelationGetRelationName(rel));

	/*
	 * WAL log creation of pages if the relation is persistent, or this is the
	 * init fork.  Init forks for unlogged relations always need to be WAL
	 * logged.
	 */
	use_wal = RelationNeedsWAL(rel) || forkNum == INIT_FORKNUM;

	/*
	 * Determine the target fill factor (in tuples per bucket) for this index.
	 * The idea is to make the fill factor correspond to pages about as full
	 * as the user-settable fillfactor parameter says.  We can compute it
	 * exactly since the index datatype (i.e. uint32 hash key) is fixed-width.
	 */
	data_width = sizeof(uint32);
	item_width = MAXALIGN(sizeof(IndexTupleData)) + MAXALIGN(data_width) +
		sizeof(ItemIdData);		/* include the line pointer */
	ffactor = RelationGetTargetPageUsage(rel, HASH_DEFAULT_FILLFACTOR) / item_width;
	/* keep to a sane range */
	if (ffactor < 10)
		ffactor = 10;

	procid = index_getprocid(rel, 1, HASHSTANDARD_PROC);

	/*
	 * We initialize the metapage, the first N bucket pages, and the first
	 * bitmap page in sequence, using _hash_getnewbuf to cause smgrextend()
	 * calls to occur.  This ensures that the smgr level has the right idea of
	 * the physical index length.
	 *
	 * Critical section not required, because on error the creation of the
	 * whole relation will be rolled back.
	 */
	metabuf = _hash_getnewbuf(rel, HASH_METAPAGE, forkNum);
	_hash_init_metabuffer(metabuf, num_tuples, procid, ffactor, false);
	MarkBufferDirty(metabuf);

	pg = BufferGetPage(metabuf);
	metap = HashPageGetMeta(pg);

	/* XLOG stuff */
	if (use_wal)
	{
		xl_hash_init_meta_page xlrec;
		XLogRecPtr	recptr;

		xlrec.num_tuples = num_tuples;
		xlrec.procid = metap->hashm_procid;
		xlrec.ffactor = metap->hashm_ffactor;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHashInitMetaPage);
		XLogRegisterBuffer(0, metabuf, REGBUF_WILL_INIT | REGBUF_STANDARD);

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_INIT_META_PAGE);

		PageSetLSN(BufferGetPage(metabuf), recptr);
	}

	num_buckets = metap->hashm_maxbucket + 1;

	/*
	 * Release buffer lock on the metapage while we initialize buckets.
	 * Otherwise, we'll be in interrupt holdoff and the CHECK_FOR_INTERRUPTS
	 * won't accomplish anything.  It's a bad idea to hold buffer locks for
	 * long intervals in any case, since that can block the bgwriter.
	 */
	LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);

	/*
	 * Initialize and WAL Log the first N buckets
	 */
	for (i = 0; i < num_buckets; i++)
	{
		BlockNumber blkno;

		/* Allow interrupts, in case N is huge */
		CHECK_FOR_INTERRUPTS();

		blkno = BUCKET_TO_BLKNO(metap, i);
		buf = _hash_getnewbuf(rel, blkno, forkNum);
		_hash_initbuf(buf, metap->hashm_maxbucket, i, LH_BUCKET_PAGE, false);
		MarkBufferDirty(buf);

		if (use_wal)
			log_newpage(&rel->rd_node,
						forkNum,
						blkno,
						BufferGetPage(buf),
						true);
		_hash_relbuf(rel, buf);
	}

	/* Now reacquire buffer lock on metapage */
	LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);

	/*
	 * Initialize bitmap page
	 */
	bitmapbuf = _hash_getnewbuf(rel, num_buckets + 1, forkNum);
	_hash_initbitmapbuffer(bitmapbuf, metap->hashm_bmsize, false);
	MarkBufferDirty(bitmapbuf);

	/* add the new bitmap page to the metapage's list of bitmaps */
	/* metapage already has a write lock */
	if (metap->hashm_nmaps >= HASH_MAX_BITMAPS)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("out of overflow pages in hash index \"%s\"",
						RelationGetRelationName(rel))));

	metap->hashm_mapp[metap->hashm_nmaps] = num_buckets + 1;

	metap->hashm_nmaps++;
	MarkBufferDirty(metabuf);

	/* XLOG stuff */
	if (use_wal)
	{
		xl_hash_init_bitmap_page xlrec;
		XLogRecPtr	recptr;

		xlrec.bmsize = metap->hashm_bmsize;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHashInitBitmapPage);
		XLogRegisterBuffer(0, bitmapbuf, REGBUF_WILL_INIT);

		/*
		 * This is safe only because nobody else can be modifying the index at
		 * this stage; it's only visible to the transaction that is creating
		 * it.
		 */
		XLogRegisterBuffer(1, metabuf, REGBUF_STANDARD);

		recptr = XLogInsert(RM_HASH_ID, XLOG_HASH_INIT_BITMAP_PAGE);

		PageSetLSN(BufferGetPage(bitmapbuf), recptr);
		PageSetLSN(BufferGetPage(metabuf), recptr);
	}

	/* all done */
	_hash_relbuf(rel, bitmapbuf);
	_hash_relbuf(rel, metabuf);

	return num_buckets;
}