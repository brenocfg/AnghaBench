#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ndeleted; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ ginxlogDeleteListPages ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GinMetaPageData ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIN_DELETED ; 
 scalar_t__ GIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  GinInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinInitMetabuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ginRedoDeleteListPages(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogDeleteListPages *data = (ginxlogDeleteListPages *) XLogRecGetData(record);
	Buffer		metabuffer;
	Page		metapage;
	int			i;

	metabuffer = XLogInitBufferForRedo(record, 0);
	Assert(BufferGetBlockNumber(metabuffer) == GIN_METAPAGE_BLKNO);
	metapage = BufferGetPage(metabuffer);

	GinInitMetabuffer(metabuffer);

	memcpy(GinPageGetMeta(metapage), &data->metadata, sizeof(GinMetaPageData));
	PageSetLSN(metapage, lsn);
	MarkBufferDirty(metabuffer);

	/*
	 * In normal operation, shiftList() takes exclusive lock on all the
	 * pages-to-be-deleted simultaneously.  During replay, however, it should
	 * be all right to lock them one at a time.  This is dependent on the fact
	 * that we are deleting pages from the head of the list, and that readers
	 * share-lock the next page before releasing the one they are on. So we
	 * cannot get past a reader that is on, or due to visit, any page we are
	 * going to delete.  New incoming readers will block behind our metapage
	 * lock and then see a fully updated page list.
	 *
	 * No full-page images are taken of the deleted pages. Instead, they are
	 * re-initialized as empty, deleted pages. Their right-links don't need to
	 * be preserved, because no new readers can see the pages, as explained
	 * above.
	 */
	for (i = 0; i < data->ndeleted; i++)
	{
		Buffer		buffer;
		Page		page;

		buffer = XLogInitBufferForRedo(record, i + 1);
		page = BufferGetPage(buffer);
		GinInitBuffer(buffer, GIN_DELETED);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);

		UnlockReleaseBuffer(buffer);
	}
	UnlockReleaseBuffer(metabuffer);
}