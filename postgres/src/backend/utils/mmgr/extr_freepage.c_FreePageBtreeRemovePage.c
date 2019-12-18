#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int nused; scalar_t__ magic; int /*<<< orphan*/  parent; } ;
struct TYPE_19__ {int /*<<< orphan*/ * internal_key; int /*<<< orphan*/ * leaf_key; } ;
struct TYPE_22__ {TYPE_2__ hdr; TYPE_1__ u; } ;
struct TYPE_21__ {scalar_t__ singleton_first_page; scalar_t__ singleton_npages; scalar_t__ btree_depth; int /*<<< orphan*/  btree_root; } ;
typedef  int Size ;
typedef  TYPE_3__ FreePageManager ;
typedef  int /*<<< orphan*/  FreePageBtreeLeafKey ;
typedef  int /*<<< orphan*/  FreePageBtreeInternalKey ;
typedef  TYPE_4__ FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FREE_PAGE_LEAF_MAGIC ; 
 int /*<<< orphan*/  FreePageBtreeAdjustAncestorKeys (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  FreePageBtreeConsolidate (TYPE_3__*,TYPE_4__*) ; 
 int FreePageBtreeFirstKey (TYPE_4__*) ; 
 int /*<<< orphan*/  FreePageBtreeRecycle (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int FreePageBtreeSearchInternal (TYPE_4__*,int) ; 
 int FreePageBtreeSearchLeaf (TYPE_4__*,int) ; 
 int /*<<< orphan*/  fpm_pointer_to_page (char*,TYPE_4__*) ; 
 char* fpm_segment_base (TYPE_3__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_store (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
FreePageBtreeRemovePage(FreePageManager *fpm, FreePageBtree *btp)
{
	char	   *base = fpm_segment_base(fpm);
	FreePageBtree *parent;
	Size		index;
	Size		first_page;

	for (;;)
	{
		/* Find parent page. */
		parent = relptr_access(base, btp->hdr.parent);
		if (parent == NULL)
		{
			/* We are removing the root page. */
			relptr_store(base, fpm->btree_root, (FreePageBtree *) NULL);
			fpm->btree_depth = 0;
			Assert(fpm->singleton_first_page == 0);
			Assert(fpm->singleton_npages == 0);
			return;
		}

		/*
		 * If the parent contains only one item, we need to remove it as well.
		 */
		if (parent->hdr.nused > 1)
			break;
		FreePageBtreeRecycle(fpm, fpm_pointer_to_page(base, btp));
		btp = parent;
	}

	/* Find and remove the downlink. */
	first_page = FreePageBtreeFirstKey(btp);
	if (parent->hdr.magic == FREE_PAGE_LEAF_MAGIC)
	{
		index = FreePageBtreeSearchLeaf(parent, first_page);
		Assert(index < parent->hdr.nused);
		if (index < parent->hdr.nused - 1)
			memmove(&parent->u.leaf_key[index],
					&parent->u.leaf_key[index + 1],
					sizeof(FreePageBtreeLeafKey)
					* (parent->hdr.nused - index - 1));
	}
	else
	{
		index = FreePageBtreeSearchInternal(parent, first_page);
		Assert(index < parent->hdr.nused);
		if (index < parent->hdr.nused - 1)
			memmove(&parent->u.internal_key[index],
					&parent->u.internal_key[index + 1],
					sizeof(FreePageBtreeInternalKey)
					* (parent->hdr.nused - index - 1));
	}
	parent->hdr.nused--;
	Assert(parent->hdr.nused > 0);

	/* Recycle the page. */
	FreePageBtreeRecycle(fpm, fpm_pointer_to_page(base, btp));

	/* Adjust ancestor keys if needed. */
	if (index == 0)
		FreePageBtreeAdjustAncestorKeys(fpm, parent);

	/* Consider whether to consolidate the parent with a sibling. */
	FreePageBtreeConsolidate(fpm, parent);
}