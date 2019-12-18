#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ clear_dead_marking; scalar_t__ is_primary_bucket_page; } ;
typedef  TYPE_1__ xl_hash_delete ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_11__ {int /*<<< orphan*/  hasho_flag; } ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_3__* HashPageOpaque ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LH_PAGE_HAS_DEAD_TUPLES ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogReadBufferForRedoExtended (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int,scalar_t__*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 

__attribute__((used)) static void
hash_xlog_delete(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_hash_delete *xldata = (xl_hash_delete *) XLogRecGetData(record);
	Buffer		bucketbuf = InvalidBuffer;
	Buffer		deletebuf;
	Page		page;
	XLogRedoAction action;

	/*
	 * Ensure we have a cleanup lock on primary bucket page before we start
	 * with the actual replay operation.  This is to ensure that neither a
	 * scan can start nor a scan can be already-in-progress during the replay
	 * of this operation.  If we allow scans during this operation, then they
	 * can miss some records or show the same record multiple times.
	 */
	if (xldata->is_primary_bucket_page)
		action = XLogReadBufferForRedoExtended(record, 1, RBM_NORMAL, true, &deletebuf);
	else
	{
		/*
		 * we don't care for return value as the purpose of reading bucketbuf
		 * is to ensure a cleanup lock on primary bucket page.
		 */
		(void) XLogReadBufferForRedoExtended(record, 0, RBM_NORMAL, true, &bucketbuf);

		action = XLogReadBufferForRedo(record, 1, &deletebuf);
	}

	/* replay the record for deleting entries in bucket page */
	if (action == BLK_NEEDS_REDO)
	{
		char	   *ptr;
		Size		len;

		ptr = XLogRecGetBlockData(record, 1, &len);

		page = (Page) BufferGetPage(deletebuf);

		if (len > 0)
		{
			OffsetNumber *unused;
			OffsetNumber *unend;

			unused = (OffsetNumber *) ptr;
			unend = (OffsetNumber *) ((char *) ptr + len);

			if ((unend - unused) > 0)
				PageIndexMultiDelete(page, unused, unend - unused);
		}

		/*
		 * Mark the page as not containing any LP_DEAD items only if
		 * clear_dead_marking flag is set to true. See comments in
		 * hashbucketcleanup() for details.
		 */
		if (xldata->clear_dead_marking)
		{
			HashPageOpaque pageopaque;

			pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
			pageopaque->hasho_flag &= ~LH_PAGE_HAS_DEAD_TUPLES;
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(deletebuf);
	}
	if (BufferIsValid(deletebuf))
		UnlockReleaseBuffer(deletebuf);

	if (BufferIsValid(bucketbuf))
		UnlockReleaseBuffer(bucketbuf);
}