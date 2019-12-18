#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ magic; int nused; } ;
struct TYPE_11__ {int /*<<< orphan*/ * internal_key; int /*<<< orphan*/ * leaf_key; } ;
struct TYPE_13__ {TYPE_2__ hdr; TYPE_1__ u; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  FreePageManager ;
typedef  int /*<<< orphan*/  FreePageBtreeLeafKey ;
typedef  int /*<<< orphan*/  FreePageBtreeInternalKey ;
typedef  TYPE_3__ FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int FPM_ITEMS_PER_INTERNAL_PAGE ; 
 int FPM_ITEMS_PER_LEAF_PAGE ; 
 scalar_t__ FREE_PAGE_INTERNAL_MAGIC ; 
 scalar_t__ FREE_PAGE_LEAF_MAGIC ; 
 TYPE_3__* FreePageBtreeFindLeftSibling (char*,TYPE_3__*) ; 
 TYPE_3__* FreePageBtreeFindRightSibling (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  FreePageBtreeRemovePage (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FreePageBtreeUpdateParentPointers (char*,TYPE_3__*) ; 
 char* fpm_segment_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
FreePageBtreeConsolidate(FreePageManager *fpm, FreePageBtree *btp)
{
	char	   *base = fpm_segment_base(fpm);
	FreePageBtree *np;
	Size		max;

	/*
	 * We only try to consolidate pages that are less than a third full. We
	 * could be more aggressive about this, but that might risk performing
	 * consolidation only to end up splitting again shortly thereafter.  Since
	 * the btree should be very small compared to the space under management,
	 * our goal isn't so much to ensure that it always occupies the absolutely
	 * smallest possible number of pages as to reclaim pages before things get
	 * too egregiously out of hand.
	 */
	if (btp->hdr.magic == FREE_PAGE_LEAF_MAGIC)
		max = FPM_ITEMS_PER_LEAF_PAGE;
	else
	{
		Assert(btp->hdr.magic == FREE_PAGE_INTERNAL_MAGIC);
		max = FPM_ITEMS_PER_INTERNAL_PAGE;
	}
	if (btp->hdr.nused >= max / 3)
		return;

	/*
	 * If we can fit our right sibling's keys onto this page, consolidate.
	 */
	np = FreePageBtreeFindRightSibling(base, btp);
	if (np != NULL && btp->hdr.nused + np->hdr.nused <= max)
	{
		if (btp->hdr.magic == FREE_PAGE_LEAF_MAGIC)
		{
			memcpy(&btp->u.leaf_key[btp->hdr.nused], &np->u.leaf_key[0],
				   sizeof(FreePageBtreeLeafKey) * np->hdr.nused);
			btp->hdr.nused += np->hdr.nused;
		}
		else
		{
			memcpy(&btp->u.internal_key[btp->hdr.nused], &np->u.internal_key[0],
				   sizeof(FreePageBtreeInternalKey) * np->hdr.nused);
			btp->hdr.nused += np->hdr.nused;
			FreePageBtreeUpdateParentPointers(base, btp);
		}
		FreePageBtreeRemovePage(fpm, np);
		return;
	}

	/*
	 * If we can fit our keys onto our left sibling's page, consolidate. In
	 * this case, we move our keys onto the other page rather than vice versa,
	 * to avoid having to adjust ancestor keys.
	 */
	np = FreePageBtreeFindLeftSibling(base, btp);
	if (np != NULL && btp->hdr.nused + np->hdr.nused <= max)
	{
		if (btp->hdr.magic == FREE_PAGE_LEAF_MAGIC)
		{
			memcpy(&np->u.leaf_key[np->hdr.nused], &btp->u.leaf_key[0],
				   sizeof(FreePageBtreeLeafKey) * btp->hdr.nused);
			np->hdr.nused += btp->hdr.nused;
		}
		else
		{
			memcpy(&np->u.internal_key[np->hdr.nused], &btp->u.internal_key[0],
				   sizeof(FreePageBtreeInternalKey) * btp->hdr.nused);
			np->hdr.nused += btp->hdr.nused;
			FreePageBtreeUpdateParentPointers(base, np);
		}
		FreePageBtreeRemovePage(fpm, btp);
		return;
	}
}