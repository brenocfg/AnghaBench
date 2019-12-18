#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* internal_key; TYPE_1__* leaf_key; } ;
struct TYPE_10__ {scalar_t__ nused; scalar_t__ magic; int /*<<< orphan*/  parent; } ;
struct TYPE_13__ {TYPE_4__ u; TYPE_2__ hdr; } ;
struct TYPE_11__ {size_t first_page; int /*<<< orphan*/  child; } ;
struct TYPE_9__ {size_t first_page; } ;
typedef  size_t Size ;
typedef  int /*<<< orphan*/  FreePageManager ;
typedef  TYPE_5__ FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FPM_ITEMS_PER_INTERNAL_PAGE ; 
 scalar_t__ FPM_ITEMS_PER_LEAF_PAGE ; 
 scalar_t__ FREE_PAGE_INTERNAL_MAGIC ; 
 scalar_t__ FREE_PAGE_LEAF_MAGIC ; 
 size_t FreePageBtreeSearchInternal (TYPE_5__*,size_t) ; 
 char* fpm_segment_base (int /*<<< orphan*/ *) ; 
 TYPE_5__* relptr_access (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FreePageBtreeAdjustAncestorKeys(FreePageManager *fpm, FreePageBtree *btp)
{
	char	   *base = fpm_segment_base(fpm);
	Size		first_page;
	FreePageBtree *parent;
	FreePageBtree *child;

	/* This might be either a leaf or an internal page. */
	Assert(btp->hdr.nused > 0);
	if (btp->hdr.magic == FREE_PAGE_LEAF_MAGIC)
	{
		Assert(btp->hdr.nused <= FPM_ITEMS_PER_LEAF_PAGE);
		first_page = btp->u.leaf_key[0].first_page;
	}
	else
	{
		Assert(btp->hdr.magic == FREE_PAGE_INTERNAL_MAGIC);
		Assert(btp->hdr.nused <= FPM_ITEMS_PER_INTERNAL_PAGE);
		first_page = btp->u.internal_key[0].first_page;
	}
	child = btp;

	/* Loop until we find an ancestor that does not require adjustment. */
	for (;;)
	{
		Size		s;

		parent = relptr_access(base, child->hdr.parent);
		if (parent == NULL)
			break;
		s = FreePageBtreeSearchInternal(parent, first_page);

		/* Key is either at index s or index s-1; figure out which. */
		if (s >= parent->hdr.nused)
		{
			Assert(s == parent->hdr.nused);
			--s;
		}
		else
		{
			FreePageBtree *check;

			check = relptr_access(base, parent->u.internal_key[s].child);
			if (check != child)
			{
				Assert(s > 0);
				--s;
			}
		}

#ifdef USE_ASSERT_CHECKING
		/* Debugging double-check. */
		{
			FreePageBtree *check;

			check = relptr_access(base, parent->u.internal_key[s].child);
			Assert(s < parent->hdr.nused);
			Assert(child == check);
		}
#endif

		/* Update the parent key. */
		parent->u.internal_key[s].first_page = first_page;

		/*
		 * If this is the first key in the parent, go up another level; else
		 * done.
		 */
		if (s > 0)
			break;
		child = parent;
	}
}