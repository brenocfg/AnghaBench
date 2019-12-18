#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  storeRes_func ;
struct TYPE_9__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_8__ {scalar_t__ tupstate; scalar_t__ nextOffset; int /*<<< orphan*/  heapPtr; } ;
struct TYPE_7__ {int /*<<< orphan*/  heapPtr; } ;
typedef  TYPE_1__ SpGistSearchItem ;
typedef  int /*<<< orphan*/  SpGistScanOpaque ;
typedef  TYPE_2__* SpGistLeafTuple ;
typedef  TYPE_3__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SPGIST_DEAD ; 
 scalar_t__ SPGIST_LIVE ; 
 scalar_t__ SPGIST_METAPAGE_BLKNO ; 
 scalar_t__ SPGIST_REDIRECT ; 
 scalar_t__ SpGistBreakOffsetNumber ; 
 scalar_t__ SpGistErrorOffsetNumber ; 
 scalar_t__ SpGistRedirectOffsetNumber ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spgLeafTest (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OffsetNumber
spgTestLeafTuple(SpGistScanOpaque so,
				 SpGistSearchItem *item,
				 Page page, OffsetNumber offset,
				 bool isnull, bool isroot,
				 bool *reportedSome,
				 storeRes_func storeRes)
{
	SpGistLeafTuple leafTuple = (SpGistLeafTuple)
	PageGetItem(page, PageGetItemId(page, offset));

	if (leafTuple->tupstate != SPGIST_LIVE)
	{
		if (!isroot)			/* all tuples on root should be live */
		{
			if (leafTuple->tupstate == SPGIST_REDIRECT)
			{
				/* redirection tuple should be first in chain */
				Assert(offset == ItemPointerGetOffsetNumber(&item->heapPtr));
				/* transfer attention to redirect point */
				item->heapPtr = ((SpGistDeadTuple) leafTuple)->pointer;
				Assert(ItemPointerGetBlockNumber(&item->heapPtr) != SPGIST_METAPAGE_BLKNO);
				return SpGistRedirectOffsetNumber;
			}

			if (leafTuple->tupstate == SPGIST_DEAD)
			{
				/* dead tuple should be first in chain */
				Assert(offset == ItemPointerGetOffsetNumber(&item->heapPtr));
				/* No live entries on this page */
				Assert(leafTuple->nextOffset == InvalidOffsetNumber);
				return SpGistBreakOffsetNumber;
			}
		}

		/* We should not arrive at a placeholder */
		elog(ERROR, "unexpected SPGiST tuple state: %d", leafTuple->tupstate);
		return SpGistErrorOffsetNumber;
	}

	Assert(ItemPointerIsValid(&leafTuple->heapPtr));

	spgLeafTest(so, item, leafTuple, isnull, reportedSome, storeRes);

	return leafTuple->nextOffset;
}