#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_14__ {scalar_t__ pageDataCxt; scalar_t__ nPageData; scalar_t__ curPageData; int /*<<< orphan*/  qual_ok; } ;
struct TYPE_11__ {int /*<<< orphan*/  parentlsn; } ;
struct TYPE_13__ {int /*<<< orphan*/ * distances; TYPE_1__ data; int /*<<< orphan*/  blkno; } ;
struct TYPE_12__ {int /*<<< orphan*/ * xs_hitup; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GistNSN ;
typedef  TYPE_3__ GISTSearchItem ;
typedef  TYPE_4__* GISTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  MemoryContextReset (scalar_t__) ; 
 TYPE_3__* getNextGISTSearchItem (TYPE_4__*) ; 
 int /*<<< orphan*/  gistScanPage (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pgstat_count_index_scan (int /*<<< orphan*/ ) ; 

int64
gistgetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	GISTScanOpaque so = (GISTScanOpaque) scan->opaque;
	int64		ntids = 0;
	GISTSearchItem fakeItem;

	if (!so->qual_ok)
		return 0;

	pgstat_count_index_scan(scan->indexRelation);

	/* Begin the scan by processing the root page */
	so->curPageData = so->nPageData = 0;
	scan->xs_hitup = NULL;
	if (so->pageDataCxt)
		MemoryContextReset(so->pageDataCxt);

	fakeItem.blkno = GIST_ROOT_BLKNO;
	memset(&fakeItem.data.parentlsn, 0, sizeof(GistNSN));
	gistScanPage(scan, &fakeItem, NULL, tbm, &ntids);

	/*
	 * While scanning a leaf page, ItemPointers of matching heap tuples will
	 * be stored directly into tbm, so we don't need to deal with them here.
	 */
	for (;;)
	{
		GISTSearchItem *item = getNextGISTSearchItem(so);

		if (!item)
			break;

		CHECK_FOR_INTERRUPTS();

		gistScanPage(scan, item, item->distances, tbm, &ntids);

		pfree(item);
	}

	return ntids;
}