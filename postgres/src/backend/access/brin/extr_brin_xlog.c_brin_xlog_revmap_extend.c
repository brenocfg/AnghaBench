#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int targetBlk; } ;
typedef  TYPE_1__ xl_brin_revmap_extend ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_11__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_13__ {int lastRevmapPage; } ;
struct TYPE_12__ {int pd_lower; } ;
typedef  TYPE_3__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_4__ BrinMetaPageData ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BRIN_PAGETYPE_REVMAP ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetContents (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  brin_page_init (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brin_xlog_revmap_extend(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_brin_revmap_extend *xlrec;
	Buffer		metabuf;
	Buffer		buf;
	Page		page;
	BlockNumber targetBlk;
	XLogRedoAction action;

	xlrec = (xl_brin_revmap_extend *) XLogRecGetData(record);

	XLogRecGetBlockTag(record, 1, NULL, NULL, &targetBlk);
	Assert(xlrec->targetBlk == targetBlk);

	/* Update the metapage */
	action = XLogReadBufferForRedo(record, 0, &metabuf);
	if (action == BLK_NEEDS_REDO)
	{
		Page		metapg;
		BrinMetaPageData *metadata;

		metapg = BufferGetPage(metabuf);
		metadata = (BrinMetaPageData *) PageGetContents(metapg);

		Assert(metadata->lastRevmapPage == xlrec->targetBlk - 1);
		metadata->lastRevmapPage = xlrec->targetBlk;

		PageSetLSN(metapg, lsn);

		/*
		 * Set pd_lower just past the end of the metadata.  This is essential,
		 * because without doing so, metadata will be lost if xlog.c
		 * compresses the page.  (We must do this here because pre-v11
		 * versions of PG did not set the metapage's pd_lower correctly, so a
		 * pg_upgraded index might contain the wrong value.)
		 */
		((PageHeader) metapg)->pd_lower =
			((char *) metadata + sizeof(BrinMetaPageData)) - (char *) metapg;

		MarkBufferDirty(metabuf);
	}

	/*
	 * Re-init the target block as a revmap page.  There's never a full- page
	 * image here.
	 */

	buf = XLogInitBufferForRedo(record, 1);
	page = (Page) BufferGetPage(buf);
	brin_page_init(page, BRIN_PAGETYPE_REVMAP);

	PageSetLSN(page, lsn);
	MarkBufferDirty(buf);

	UnlockReleaseBuffer(buf);
	if (BufferIsValid(metabuf))
		UnlockReleaseBuffer(metabuf);
}