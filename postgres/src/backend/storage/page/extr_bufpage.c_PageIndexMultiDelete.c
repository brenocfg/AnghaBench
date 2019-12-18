#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offsetindex; unsigned int itemoff; unsigned int alignedlen; } ;
typedef  TYPE_1__ itemIdSortData ;
typedef  TYPE_1__* itemIdSort ;
struct TYPE_6__ {scalar_t__ pd_lower; scalar_t__ pd_upper; scalar_t__ pd_special; int /*<<< orphan*/  pd_linp; } ;
typedef  unsigned int Size ;
typedef  TYPE_3__* PageHeader ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  scalar_t__ Offset ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/ * ItemId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstOffsetNumber ; 
 unsigned int ItemIdGetLength (int /*<<< orphan*/ *) ; 
 unsigned int ItemIdGetOffset (int /*<<< orphan*/ *) ; 
 int ItemIdHasStorage (int /*<<< orphan*/ *) ; 
 unsigned int MAXALIGN (unsigned int) ; 
 int MaxIndexTuplesPerPage ; 
 int OffsetNumberNext (int) ; 
 int /*<<< orphan*/ * PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  compactify_tuples (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,unsigned int,scalar_t__,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
PageIndexMultiDelete(Page page, OffsetNumber *itemnos, int nitems)
{
	PageHeader	phdr = (PageHeader) page;
	Offset		pd_lower = phdr->pd_lower;
	Offset		pd_upper = phdr->pd_upper;
	Offset		pd_special = phdr->pd_special;
	itemIdSortData itemidbase[MaxIndexTuplesPerPage];
	ItemIdData	newitemids[MaxIndexTuplesPerPage];
	itemIdSort	itemidptr;
	ItemId		lp;
	int			nline,
				nused;
	Size		totallen;
	Size		size;
	unsigned	offset;
	int			nextitm;
	OffsetNumber offnum;

	Assert(nitems <= MaxIndexTuplesPerPage);

	/*
	 * If there aren't very many items to delete, then retail
	 * PageIndexTupleDelete is the best way.  Delete the items in reverse
	 * order so we don't have to think about adjusting item numbers for
	 * previous deletions.
	 *
	 * TODO: tune the magic number here
	 */
	if (nitems <= 2)
	{
		while (--nitems >= 0)
			PageIndexTupleDelete(page, itemnos[nitems]);
		return;
	}

	/*
	 * As with PageRepairFragmentation, paranoia seems justified.
	 */
	if (pd_lower < SizeOfPageHeaderData ||
		pd_lower > pd_upper ||
		pd_upper > pd_special ||
		pd_special > BLCKSZ ||
		pd_special != MAXALIGN(pd_special))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("corrupted page pointers: lower = %u, upper = %u, special = %u",
						pd_lower, pd_upper, pd_special)));

	/*
	 * Scan the line pointer array and build a list of just the ones we are
	 * going to keep.  Notice we do not modify the page yet, since we are
	 * still validity-checking.
	 */
	nline = PageGetMaxOffsetNumber(page);
	itemidptr = itemidbase;
	totallen = 0;
	nused = 0;
	nextitm = 0;
	for (offnum = FirstOffsetNumber; offnum <= nline; offnum = OffsetNumberNext(offnum))
	{
		lp = PageGetItemId(page, offnum);
		Assert(ItemIdHasStorage(lp));
		size = ItemIdGetLength(lp);
		offset = ItemIdGetOffset(lp);
		if (offset < pd_upper ||
			(offset + size) > pd_special ||
			offset != MAXALIGN(offset))
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("corrupted line pointer: offset = %u, size = %u",
							offset, (unsigned int) size)));

		if (nextitm < nitems && offnum == itemnos[nextitm])
		{
			/* skip item to be deleted */
			nextitm++;
		}
		else
		{
			itemidptr->offsetindex = nused; /* where it will go */
			itemidptr->itemoff = offset;
			itemidptr->alignedlen = MAXALIGN(size);
			totallen += itemidptr->alignedlen;
			newitemids[nused] = *lp;
			itemidptr++;
			nused++;
		}
	}

	/* this will catch invalid or out-of-order itemnos[] */
	if (nextitm != nitems)
		elog(ERROR, "incorrect index offsets supplied");

	if (totallen > (Size) (pd_special - pd_lower))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("corrupted item lengths: total %u, available space %u",
						(unsigned int) totallen, pd_special - pd_lower)));

	/*
	 * Looks good. Overwrite the line pointers with the copy, from which we've
	 * removed all the unused items.
	 */
	memcpy(phdr->pd_linp, newitemids, nused * sizeof(ItemIdData));
	phdr->pd_lower = SizeOfPageHeaderData + nused * sizeof(ItemIdData);

	/* and compactify the tuple data */
	compactify_tuples(itemidbase, nused, page);
}