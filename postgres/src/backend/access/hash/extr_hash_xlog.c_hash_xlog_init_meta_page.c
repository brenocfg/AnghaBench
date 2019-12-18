#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ffactor; int /*<<< orphan*/  procid; int /*<<< orphan*/  num_tuples; } ;
typedef  TYPE_1__ xl_hash_init_meta_page ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushOneBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ INIT_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  _hash_init_metabuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hash_xlog_init_meta_page(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	Page		page;
	Buffer		metabuf;
	ForkNumber	forknum;

	xl_hash_init_meta_page *xlrec = (xl_hash_init_meta_page *) XLogRecGetData(record);

	/* create the index' metapage */
	metabuf = XLogInitBufferForRedo(record, 0);
	Assert(BufferIsValid(metabuf));
	_hash_init_metabuffer(metabuf, xlrec->num_tuples, xlrec->procid,
						  xlrec->ffactor, true);
	page = (Page) BufferGetPage(metabuf);
	PageSetLSN(page, lsn);
	MarkBufferDirty(metabuf);

	/*
	 * Force the on-disk state of init forks to always be in sync with the
	 * state in shared buffers.  See XLogReadBufferForRedoExtended.  We need
	 * special handling for init forks as create index operations don't log a
	 * full page image of the metapage.
	 */
	XLogRecGetBlockTag(record, 0, NULL, &forknum, NULL);
	if (forknum == INIT_FORKNUM)
		FlushOneBuffer(metabuf);

	/* all done */
	UnlockReleaseBuffer(metabuf);
}