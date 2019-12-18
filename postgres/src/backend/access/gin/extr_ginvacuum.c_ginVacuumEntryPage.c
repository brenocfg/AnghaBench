#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  index; int /*<<< orphan*/  ginstate; } ;
typedef  int /*<<< orphan*/ * Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  TYPE_1__ GinVacuumState ;
typedef  int /*<<< orphan*/  GinPostingList ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/ * GinFormTuple (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  GinGetDownlink (int /*<<< orphan*/ *) ; 
 int GinGetNPosting (int /*<<< orphan*/ *) ; 
 scalar_t__ GinGetPosting (int /*<<< orphan*/ *) ; 
 scalar_t__ GinIsPostingTree (int /*<<< orphan*/ *) ; 
 scalar_t__ GinItupIsCompressed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GinMaxItemSize ; 
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ *) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetTempPageCopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int SizeOfGinPostingList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ginCompressPostingList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ginPostingListDecode (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * ginVacuumItemPointers (TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ gintuple_get_attrnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gintuple_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Page
ginVacuumEntryPage(GinVacuumState *gvs, Buffer buffer, BlockNumber *roots, uint32 *nroot)
{
	Page		origpage = BufferGetPage(buffer),
				tmppage;
	OffsetNumber i,
				maxoff = PageGetMaxOffsetNumber(origpage);

	tmppage = origpage;

	*nroot = 0;

	for (i = FirstOffsetNumber; i <= maxoff; i++)
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(tmppage, PageGetItemId(tmppage, i));

		if (GinIsPostingTree(itup))
		{
			/*
			 * store posting tree's roots for further processing, we can't
			 * vacuum it just now due to risk of deadlocks with scans/inserts
			 */
			roots[*nroot] = GinGetDownlink(itup);
			(*nroot)++;
		}
		else if (GinGetNPosting(itup) > 0)
		{
			int			nitems;
			ItemPointer items_orig;
			bool		free_items_orig;
			ItemPointer items;

			/* Get list of item pointers from the tuple. */
			if (GinItupIsCompressed(itup))
			{
				items_orig = ginPostingListDecode((GinPostingList *) GinGetPosting(itup), &nitems);
				free_items_orig = true;
			}
			else
			{
				items_orig = (ItemPointer) GinGetPosting(itup);
				nitems = GinGetNPosting(itup);
				free_items_orig = false;
			}

			/* Remove any items from the list that need to be vacuumed. */
			items = ginVacuumItemPointers(gvs, items_orig, nitems, &nitems);

			if (free_items_orig)
				pfree(items_orig);

			/* If any item pointers were removed, recreate the tuple. */
			if (items)
			{
				OffsetNumber attnum;
				Datum		key;
				GinNullCategory category;
				GinPostingList *plist;
				int			plistsize;

				if (nitems > 0)
				{
					plist = ginCompressPostingList(items, nitems, GinMaxItemSize, NULL);
					plistsize = SizeOfGinPostingList(plist);
				}
				else
				{
					plist = NULL;
					plistsize = 0;
				}

				/*
				 * if we already created a temporary page, make changes in
				 * place
				 */
				if (tmppage == origpage)
				{
					/*
					 * On first difference, create a temporary copy of the
					 * page and copy the tuple's posting list to it.
					 */
					tmppage = PageGetTempPageCopy(origpage);

					/* set itup pointer to new page */
					itup = (IndexTuple) PageGetItem(tmppage, PageGetItemId(tmppage, i));
				}

				attnum = gintuple_get_attrnum(&gvs->ginstate, itup);
				key = gintuple_get_key(&gvs->ginstate, itup, &category);
				itup = GinFormTuple(&gvs->ginstate, attnum, key, category,
									(char *) plist, plistsize,
									nitems, true);
				if (plist)
					pfree(plist);
				PageIndexTupleDelete(tmppage, i);

				if (PageAddItem(tmppage, (Item) itup, IndexTupleSize(itup), i, false, false) != i)
					elog(ERROR, "failed to add item to index page in \"%s\"",
						 RelationGetRelationName(gvs->index));

				pfree(itup);
				pfree(items);
			}
		}
	}

	return (tmppage == origpage) ? NULL : tmppage;
}