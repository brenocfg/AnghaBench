#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rm_tids; } ;
typedef  TYPE_1__ RevmapContents ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAPBLK_TO_REVMAP_INDEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 

void
brinSetHeapBlockItemptr(Buffer buf, BlockNumber pagesPerRange,
						BlockNumber heapBlk, ItemPointerData tid)
{
	RevmapContents *contents;
	ItemPointerData *iptr;
	Page		page;

	/* The correct page should already be pinned and locked */
	page = BufferGetPage(buf);
	contents = (RevmapContents *) PageGetContents(page);
	iptr = (ItemPointerData *) contents->rm_tids;
	iptr += HEAPBLK_TO_REVMAP_INDEX(pagesPerRange, heapBlk);

	if (ItemPointerIsValid(&tid))
		ItemPointerSet(iptr,
					   ItemPointerGetBlockNumber(&tid),
					   ItemPointerGetOffsetNumber(&tid));
	else
		ItemPointerSetInvalid(iptr);
}