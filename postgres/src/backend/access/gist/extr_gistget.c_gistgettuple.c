#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int firstCall; int curPageData; int nPageData; int numKilled; int /*<<< orphan*/  curBlkno; TYPE_3__* pageData; int /*<<< orphan*/ * killedItems; TYPE_2__* giststate; scalar_t__ pageDataCxt; int /*<<< orphan*/  qual_ok; } ;
struct TYPE_15__ {int /*<<< orphan*/  parentlsn; } ;
struct TYPE_19__ {int /*<<< orphan*/ * distances; int /*<<< orphan*/  blkno; TYPE_1__ data; } ;
struct TYPE_18__ {scalar_t__ numberOfOrderBys; scalar_t__ kill_prior_tuple; int /*<<< orphan*/ * xs_hitup; scalar_t__ xs_want_itup; int /*<<< orphan*/  xs_recheck; int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
struct TYPE_17__ {int /*<<< orphan*/  offnum; int /*<<< orphan*/ * recontup; int /*<<< orphan*/  recheck; int /*<<< orphan*/  heapPtr; } ;
struct TYPE_16__ {int /*<<< orphan*/  scanCxt; } ;
typedef  scalar_t__ ScanDirection ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GistNSN ;
typedef  TYPE_5__ GISTSearchItem ;
typedef  TYPE_6__* GISTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ForwardScanDirection ; 
 int /*<<< orphan*/  GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int MaxIndexTuplesPerPage ; 
 int /*<<< orphan*/  MemoryContextReset (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* getNextGISTSearchItem (TYPE_6__*) ; 
 int getNextNearest (TYPE_4__*) ; 
 int /*<<< orphan*/  gistScanPage (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistkillitems (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_5__*) ; 
 int /*<<< orphan*/  pgstat_count_index_scan (int /*<<< orphan*/ ) ; 

bool
gistgettuple(IndexScanDesc scan, ScanDirection dir)
{
	GISTScanOpaque so = (GISTScanOpaque) scan->opaque;

	if (dir != ForwardScanDirection)
		elog(ERROR, "GiST only supports forward scan direction");

	if (!so->qual_ok)
		return false;

	if (so->firstCall)
	{
		/* Begin the scan by processing the root page */
		GISTSearchItem fakeItem;

		pgstat_count_index_scan(scan->indexRelation);

		so->firstCall = false;
		so->curPageData = so->nPageData = 0;
		scan->xs_hitup = NULL;
		if (so->pageDataCxt)
			MemoryContextReset(so->pageDataCxt);

		fakeItem.blkno = GIST_ROOT_BLKNO;
		memset(&fakeItem.data.parentlsn, 0, sizeof(GistNSN));
		gistScanPage(scan, &fakeItem, NULL, NULL, NULL);
	}

	if (scan->numberOfOrderBys > 0)
	{
		/* Must fetch tuples in strict distance order */
		return getNextNearest(scan);
	}
	else
	{
		/* Fetch tuples index-page-at-a-time */
		for (;;)
		{
			if (so->curPageData < so->nPageData)
			{
				if (scan->kill_prior_tuple && so->curPageData > 0)
				{

					if (so->killedItems == NULL)
					{
						MemoryContext oldCxt =
						MemoryContextSwitchTo(so->giststate->scanCxt);

						so->killedItems =
							(OffsetNumber *) palloc(MaxIndexTuplesPerPage
													* sizeof(OffsetNumber));

						MemoryContextSwitchTo(oldCxt);
					}
					if (so->numKilled < MaxIndexTuplesPerPage)
						so->killedItems[so->numKilled++] =
							so->pageData[so->curPageData - 1].offnum;
				}
				/* continuing to return tuples from a leaf page */
				scan->xs_heaptid = so->pageData[so->curPageData].heapPtr;
				scan->xs_recheck = so->pageData[so->curPageData].recheck;

				/* in an index-only scan, also return the reconstructed tuple */
				if (scan->xs_want_itup)
					scan->xs_hitup = so->pageData[so->curPageData].recontup;

				so->curPageData++;

				return true;
			}

			/*
			 * Check the last returned tuple and add it to killedItems if
			 * necessary
			 */
			if (scan->kill_prior_tuple
				&& so->curPageData > 0
				&& so->curPageData == so->nPageData)
			{

				if (so->killedItems == NULL)
				{
					MemoryContext oldCxt =
					MemoryContextSwitchTo(so->giststate->scanCxt);

					so->killedItems =
						(OffsetNumber *) palloc(MaxIndexTuplesPerPage
												* sizeof(OffsetNumber));

					MemoryContextSwitchTo(oldCxt);
				}
				if (so->numKilled < MaxIndexTuplesPerPage)
					so->killedItems[so->numKilled++] =
						so->pageData[so->curPageData - 1].offnum;
			}
			/* find and process the next index page */
			do
			{
				GISTSearchItem *item;

				if ((so->curBlkno != InvalidBlockNumber) && (so->numKilled > 0))
					gistkillitems(scan);

				item = getNextGISTSearchItem(so);

				if (!item)
					return false;

				CHECK_FOR_INTERRUPTS();

				/* save current item BlockNumber for next gistkillitems() call */
				so->curBlkno = item->blkno;

				/*
				 * While scanning a leaf page, ItemPointers of matching heap
				 * tuples are stored in so->pageData.  If there are any on
				 * this page, we fall out of the inner "do" and loop around to
				 * return them.
				 */
				gistScanPage(scan, item, item->distances, NULL, NULL);

				pfree(item);
			} while (so->nPageData == 0);
		}
	}
}