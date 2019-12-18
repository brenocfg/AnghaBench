#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  index; } ;
struct TYPE_14__ {scalar_t__ entry; } ;
struct TYPE_13__ {scalar_t__ off; } ;
struct TYPE_12__ {char* data; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ PGAlignedBlock ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__ GinBtreeStack ;
typedef  TYPE_3__ GinBtreeEntryInsertData ;
typedef  TYPE_4__* GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GinInitPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_10__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int PageGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetTempPageCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entryPreparePage (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static void
entrySplitPage(GinBtree btree, Buffer origbuf,
			   GinBtreeStack *stack,
			   GinBtreeEntryInsertData *insertData,
			   BlockNumber updateblkno,
			   Page *newlpage, Page *newrpage)
{
	OffsetNumber off = stack->off;
	OffsetNumber i,
				maxoff,
				separator = InvalidOffsetNumber;
	Size		totalsize = 0;
	Size		lsize = 0,
				size;
	char	   *ptr;
	IndexTuple	itup;
	Page		page;
	Page		lpage = PageGetTempPageCopy(BufferGetPage(origbuf));
	Page		rpage = PageGetTempPageCopy(BufferGetPage(origbuf));
	Size		pageSize = PageGetPageSize(lpage);
	PGAlignedBlock tupstore[2]; /* could need 2 pages' worth of tuples */

	entryPreparePage(btree, lpage, off, insertData, updateblkno);

	/*
	 * First, append all the existing tuples and the new tuple we're inserting
	 * one after another in a temporary workspace.
	 */
	maxoff = PageGetMaxOffsetNumber(lpage);
	ptr = tupstore[0].data;
	for (i = FirstOffsetNumber; i <= maxoff; i++)
	{
		if (i == off)
		{
			size = MAXALIGN(IndexTupleSize(insertData->entry));
			memcpy(ptr, insertData->entry, size);
			ptr += size;
			totalsize += size + sizeof(ItemIdData);
		}

		itup = (IndexTuple) PageGetItem(lpage, PageGetItemId(lpage, i));
		size = MAXALIGN(IndexTupleSize(itup));
		memcpy(ptr, itup, size);
		ptr += size;
		totalsize += size + sizeof(ItemIdData);
	}

	if (off == maxoff + 1)
	{
		size = MAXALIGN(IndexTupleSize(insertData->entry));
		memcpy(ptr, insertData->entry, size);
		ptr += size;
		totalsize += size + sizeof(ItemIdData);
	}

	/*
	 * Initialize the left and right pages, and copy all the tuples back to
	 * them.
	 */
	GinInitPage(rpage, GinPageGetOpaque(lpage)->flags, pageSize);
	GinInitPage(lpage, GinPageGetOpaque(rpage)->flags, pageSize);

	ptr = tupstore[0].data;
	maxoff++;
	lsize = 0;

	page = lpage;
	for (i = FirstOffsetNumber; i <= maxoff; i++)
	{
		itup = (IndexTuple) ptr;

		/*
		 * Decide where to split.  We try to equalize the pages' total data
		 * size, not number of tuples.
		 */
		if (lsize > totalsize / 2)
		{
			if (separator == InvalidOffsetNumber)
				separator = i - 1;
			page = rpage;
		}
		else
		{
			lsize += MAXALIGN(IndexTupleSize(itup)) + sizeof(ItemIdData);
		}

		if (PageAddItem(page, (Item) itup, IndexTupleSize(itup), InvalidOffsetNumber, false, false) == InvalidOffsetNumber)
			elog(ERROR, "failed to add item to index page in \"%s\"",
				 RelationGetRelationName(btree->index));
		ptr += MAXALIGN(IndexTupleSize(itup));
	}

	/* return temp pages to caller */
	*newlpage = lpage;
	*newrpage = rpage;
}