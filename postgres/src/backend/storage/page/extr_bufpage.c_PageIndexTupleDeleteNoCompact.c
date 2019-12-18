#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int lp_off; } ;
struct TYPE_13__ {scalar_t__ pd_lower; scalar_t__ pd_upper; scalar_t__ pd_special; } ;
typedef  unsigned int Size ;
typedef  TYPE_1__* PageHeader ;
typedef  TYPE_1__* Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  TYPE_3__* ItemId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 unsigned int ItemIdGetLength (TYPE_3__*) ; 
 unsigned int ItemIdGetOffset (TYPE_3__*) ; 
 scalar_t__ ItemIdHasStorage (TYPE_3__*) ; 
 int /*<<< orphan*/  ItemIdSetUnused (TYPE_3__*) ; 
 unsigned int MAXALIGN (unsigned int) ; 
 TYPE_3__* PageGetItemId (TYPE_1__*,int) ; 
 int PageGetMaxOffsetNumber (TYPE_1__*) ; 
 int /*<<< orphan*/  PageIsEmpty (TYPE_1__*) ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned int) ; 

void
PageIndexTupleDeleteNoCompact(Page page, OffsetNumber offnum)
{
	PageHeader	phdr = (PageHeader) page;
	char	   *addr;
	ItemId		tup;
	Size		size;
	unsigned	offset;
	int			nline;

	/*
	 * As with PageRepairFragmentation, paranoia seems justified.
	 */
	if (phdr->pd_lower < SizeOfPageHeaderData ||
		phdr->pd_lower > phdr->pd_upper ||
		phdr->pd_upper > phdr->pd_special ||
		phdr->pd_special > BLCKSZ ||
		phdr->pd_special != MAXALIGN(phdr->pd_special))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("corrupted page pointers: lower = %u, upper = %u, special = %u",
						phdr->pd_lower, phdr->pd_upper, phdr->pd_special)));

	nline = PageGetMaxOffsetNumber(page);
	if ((int) offnum <= 0 || (int) offnum > nline)
		elog(ERROR, "invalid index offnum: %u", offnum);

	tup = PageGetItemId(page, offnum);
	Assert(ItemIdHasStorage(tup));
	size = ItemIdGetLength(tup);
	offset = ItemIdGetOffset(tup);

	if (offset < phdr->pd_upper || (offset + size) > phdr->pd_special ||
		offset != MAXALIGN(offset))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("corrupted line pointer: offset = %u, size = %u",
						offset, (unsigned int) size)));

	/* Amount of space to actually be deleted */
	size = MAXALIGN(size);

	/*
	 * Either set the line pointer to "unused", or zap it if it's the last
	 * one.  (Note: it's possible that the next-to-last one(s) are already
	 * unused, but we do not trouble to try to compact them out if so.)
	 */
	if ((int) offnum < nline)
		ItemIdSetUnused(tup);
	else
	{
		phdr->pd_lower -= sizeof(ItemIdData);
		nline--;				/* there's one less than when we started */
	}

	/*
	 * Now move everything between the old upper bound (beginning of tuple
	 * space) and the beginning of the deleted tuple forward, so that space in
	 * the middle of the page is left free.  If we've just deleted the tuple
	 * at the beginning of tuple space, then there's no need to do the copy.
	 */

	/* beginning of tuple space */
	addr = (char *) page + phdr->pd_upper;

	if (offset > phdr->pd_upper)
		memmove(addr + size, addr, offset - phdr->pd_upper);

	/* adjust free space boundary pointer */
	phdr->pd_upper += size;

	/*
	 * Finally, we need to adjust the linp entries that remain.
	 *
	 * Anything that used to be before the deleted tuple's data was moved
	 * forward by the size of the deleted tuple.
	 */
	if (!PageIsEmpty(page))
	{
		int			i;

		for (i = 1; i <= nline; i++)
		{
			ItemId		ii = PageGetItemId(phdr, i);

			if (ItemIdHasStorage(ii) && ItemIdGetOffset(ii) <= offset)
				ii->lp_off += size;
		}
	}
}