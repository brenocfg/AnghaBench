#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int maxoff; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {scalar_t__ isBuild; } ;
struct TYPE_12__ {int off; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_2__ GinBtreeStack ;
typedef  TYPE_3__* GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int FirstOffsetNumber ; 
 TYPE_1__* GinDataPageGetPostingItem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GinDataPageGetRightBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinDataPageSetDataSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GinInitPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GinNonLeafDataPageGetFreeSpace (int /*<<< orphan*/ ) ; 
 TYPE_9__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetTempPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostingItemSetBlockNumber (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
dataSplitPageInternal(GinBtree btree, Buffer origbuf,
					  GinBtreeStack *stack,
					  void *insertdata, BlockNumber updateblkno,
					  Page *newlpage, Page *newrpage)
{
	Page		oldpage = BufferGetPage(origbuf);
	OffsetNumber off = stack->off;
	int			nitems = GinPageGetOpaque(oldpage)->maxoff;
	int			nleftitems;
	int			nrightitems;
	Size		pageSize = PageGetPageSize(oldpage);
	ItemPointerData oldbound = *GinDataPageGetRightBound(oldpage);
	ItemPointer bound;
	Page		lpage;
	Page		rpage;
	OffsetNumber separator;
	PostingItem allitems[(BLCKSZ / sizeof(PostingItem)) + 1];

	lpage = PageGetTempPage(oldpage);
	rpage = PageGetTempPage(oldpage);
	GinInitPage(lpage, GinPageGetOpaque(oldpage)->flags, pageSize);
	GinInitPage(rpage, GinPageGetOpaque(oldpage)->flags, pageSize);

	/*
	 * First construct a new list of PostingItems, which includes all the old
	 * items, and the new item.
	 */
	memcpy(allitems, GinDataPageGetPostingItem(oldpage, FirstOffsetNumber),
		   (off - 1) * sizeof(PostingItem));

	allitems[off - 1] = *((PostingItem *) insertdata);
	memcpy(&allitems[off], GinDataPageGetPostingItem(oldpage, off),
		   (nitems - (off - 1)) * sizeof(PostingItem));
	nitems++;

	/* Update existing downlink to point to next page */
	PostingItemSetBlockNumber(&allitems[off], updateblkno);

	/*
	 * When creating a new index, fit as many tuples as possible on the left
	 * page, on the assumption that the table is scanned from beginning to
	 * end. This packs the index as tight as possible.
	 */
	if (btree->isBuild && GinPageRightMost(oldpage))
		separator = GinNonLeafDataPageGetFreeSpace(rpage) / sizeof(PostingItem);
	else
		separator = nitems / 2;
	nleftitems = separator;
	nrightitems = nitems - separator;

	memcpy(GinDataPageGetPostingItem(lpage, FirstOffsetNumber),
		   allitems,
		   nleftitems * sizeof(PostingItem));
	GinPageGetOpaque(lpage)->maxoff = nleftitems;
	memcpy(GinDataPageGetPostingItem(rpage, FirstOffsetNumber),
		   &allitems[separator],
		   nrightitems * sizeof(PostingItem));
	GinPageGetOpaque(rpage)->maxoff = nrightitems;

	/*
	 * Also set pd_lower for both pages, like GinDataPageAddPostingItem does.
	 */
	GinDataPageSetDataSize(lpage, nleftitems * sizeof(PostingItem));
	GinDataPageSetDataSize(rpage, nrightitems * sizeof(PostingItem));

	/* set up right bound for left page */
	bound = GinDataPageGetRightBound(lpage);
	*bound = GinDataPageGetPostingItem(lpage, nleftitems)->key;

	/* set up right bound for right page */
	*GinDataPageGetRightBound(rpage) = oldbound;

	/* return temp pages to caller */
	*newlpage = lpage;
	*newrpage = rpage;
}