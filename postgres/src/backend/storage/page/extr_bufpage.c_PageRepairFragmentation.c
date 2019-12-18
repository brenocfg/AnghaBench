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
struct TYPE_5__ {int offsetindex; int itemoff; scalar_t__ alignedlen; } ;
typedef  TYPE_1__ itemIdSortData ;
typedef  TYPE_1__* itemIdSort ;
struct TYPE_6__ {scalar_t__ pd_lower; scalar_t__ pd_upper; scalar_t__ pd_special; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_3__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ Offset ;
typedef  int /*<<< orphan*/  ItemId ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstOffsetNumber ; 
 scalar_t__ ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemIdGetOffset (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdHasStorage (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdSetUnused (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int MaxHeapTuplesPerPage ; 
 int /*<<< orphan*/  PageClearHasFreeLinePointers (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int) ; 
 int PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageSetHasFreeLinePointers (scalar_t__) ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  compactify_tuples (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,unsigned int,...) ; 
 scalar_t__ unlikely (int) ; 

void
PageRepairFragmentation(Page page)
{
	Offset		pd_lower = ((PageHeader) page)->pd_lower;
	Offset		pd_upper = ((PageHeader) page)->pd_upper;
	Offset		pd_special = ((PageHeader) page)->pd_special;
	itemIdSortData itemidbase[MaxHeapTuplesPerPage];
	itemIdSort	itemidptr;
	ItemId		lp;
	int			nline,
				nstorage,
				nunused;
	int			i;
	Size		totallen;

	/*
	 * It's worth the trouble to be more paranoid here than in most places,
	 * because we are about to reshuffle data in (what is usually) a shared
	 * disk buffer.  If we aren't careful then corrupted pointers, lengths,
	 * etc could cause us to clobber adjacent disk buffers, spreading the data
	 * loss further.  So, check everything.
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
	 * Run through the line pointer array and collect data about live items.
	 */
	nline = PageGetMaxOffsetNumber(page);
	itemidptr = itemidbase;
	nunused = totallen = 0;
	for (i = FirstOffsetNumber; i <= nline; i++)
	{
		lp = PageGetItemId(page, i);
		if (ItemIdIsUsed(lp))
		{
			if (ItemIdHasStorage(lp))
			{
				itemidptr->offsetindex = i - 1;
				itemidptr->itemoff = ItemIdGetOffset(lp);
				if (unlikely(itemidptr->itemoff < (int) pd_upper ||
							 itemidptr->itemoff >= (int) pd_special))
					ereport(ERROR,
							(errcode(ERRCODE_DATA_CORRUPTED),
							 errmsg("corrupted line pointer: %u",
									itemidptr->itemoff)));
				itemidptr->alignedlen = MAXALIGN(ItemIdGetLength(lp));
				totallen += itemidptr->alignedlen;
				itemidptr++;
			}
		}
		else
		{
			/* Unused entries should have lp_len = 0, but make sure */
			ItemIdSetUnused(lp);
			nunused++;
		}
	}

	nstorage = itemidptr - itemidbase;
	if (nstorage == 0)
	{
		/* Page is completely empty, so just reset it quickly */
		((PageHeader) page)->pd_upper = pd_special;
	}
	else
	{
		/* Need to compact the page the hard way */
		if (totallen > (Size) (pd_special - pd_lower))
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("corrupted item lengths: total %u, available space %u",
							(unsigned int) totallen, pd_special - pd_lower)));

		compactify_tuples(itemidbase, nstorage, page);
	}

	/* Set hint bit for PageAddItem */
	if (nunused > 0)
		PageSetHasFreeLinePointers(page);
	else
		PageClearHasFreeLinePointers(page);
}