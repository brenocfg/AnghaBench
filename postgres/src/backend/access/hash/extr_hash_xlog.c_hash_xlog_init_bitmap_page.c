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
struct TYPE_10__ {int /*<<< orphan*/  bmsize; } ;
typedef  TYPE_1__ xl_hash_init_bitmap_page ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_11__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_12__ {size_t hashm_nmaps; scalar_t__* hashm_mapp; scalar_t__ hashm_maxbucket; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_3__* HashMetaPage ;
typedef  scalar_t__ ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushOneBuffer (int /*<<< orphan*/ ) ; 
 TYPE_3__* HashPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ INIT_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  _hash_initbitmapbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hash_xlog_init_bitmap_page(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	Buffer		bitmapbuf;
	Buffer		metabuf;
	Page		page;
	HashMetaPage metap;
	uint32		num_buckets;
	ForkNumber	forknum;

	xl_hash_init_bitmap_page *xlrec = (xl_hash_init_bitmap_page *) XLogRecGetData(record);

	/*
	 * Initialize bitmap page
	 */
	bitmapbuf = XLogInitBufferForRedo(record, 0);
	_hash_initbitmapbuffer(bitmapbuf, xlrec->bmsize, true);
	PageSetLSN(BufferGetPage(bitmapbuf), lsn);
	MarkBufferDirty(bitmapbuf);

	/*
	 * Force the on-disk state of init forks to always be in sync with the
	 * state in shared buffers.  See XLogReadBufferForRedoExtended.  We need
	 * special handling for init forks as create index operations don't log a
	 * full page image of the metapage.
	 */
	XLogRecGetBlockTag(record, 0, NULL, &forknum, NULL);
	if (forknum == INIT_FORKNUM)
		FlushOneBuffer(bitmapbuf);
	UnlockReleaseBuffer(bitmapbuf);

	/* add the new bitmap page to the metapage's list of bitmaps */
	if (XLogReadBufferForRedo(record, 1, &metabuf) == BLK_NEEDS_REDO)
	{
		/*
		 * Note: in normal operation, we'd update the metapage while still
		 * holding lock on the bitmap page.  But during replay it's not
		 * necessary to hold that lock, since nobody can see it yet; the
		 * creating transaction hasn't yet committed.
		 */
		page = BufferGetPage(metabuf);
		metap = HashPageGetMeta(page);

		num_buckets = metap->hashm_maxbucket + 1;
		metap->hashm_mapp[metap->hashm_nmaps] = num_buckets + 1;
		metap->hashm_nmaps++;

		PageSetLSN(page, lsn);
		MarkBufferDirty(metabuf);

		XLogRecGetBlockTag(record, 1, NULL, &forknum, NULL);
		if (forknum == INIT_FORKNUM)
			FlushOneBuffer(metabuf);
	}
	if (BufferIsValid(metabuf))
		UnlockReleaseBuffer(metabuf);
}