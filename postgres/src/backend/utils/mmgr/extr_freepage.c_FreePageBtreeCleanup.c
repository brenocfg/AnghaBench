#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_3__* leaf_key; TYPE_1__* internal_key; } ;
struct TYPE_19__ {int nused; scalar_t__ magic; int /*<<< orphan*/  parent; } ;
struct TYPE_23__ {TYPE_4__ u; TYPE_2__ hdr; } ;
struct TYPE_22__ {scalar_t__ btree_depth; scalar_t__ singleton_first_page; scalar_t__ singleton_npages; scalar_t__ btree_recycle_count; int /*<<< orphan*/  btree_root; } ;
struct TYPE_20__ {scalar_t__ first_page; scalar_t__ npages; } ;
struct TYPE_18__ {int /*<<< orphan*/  child; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_5__ FreePageManager ;
typedef  TYPE_6__ FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FREE_PAGE_INTERNAL_MAGIC ; 
 scalar_t__ FREE_PAGE_LEAF_MAGIC ; 
 TYPE_6__* FreePageBtreeGetRecycled (TYPE_5__*) ; 
 int /*<<< orphan*/  FreePageBtreeRecycle (TYPE_5__*,scalar_t__) ; 
 scalar_t__ FreePageManagerPutInternal (TYPE_5__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  FreePagePopSpanLeader (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  FreePagePushSpanLeader (TYPE_5__*,scalar_t__,scalar_t__) ; 
 scalar_t__ fpm_pointer_to_page (char*,TYPE_6__*) ; 
 char* fpm_segment_base (TYPE_5__*) ; 
 TYPE_6__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_store (char*,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static Size
FreePageBtreeCleanup(FreePageManager *fpm)
{
	char	   *base = fpm_segment_base(fpm);
	Size		max_contiguous_pages = 0;

	/* Attempt to shrink the depth of the btree. */
	while (!relptr_is_null(fpm->btree_root))
	{
		FreePageBtree *root = relptr_access(base, fpm->btree_root);

		/* If the root contains only one key, reduce depth by one. */
		if (root->hdr.nused == 1)
		{
			/* Shrink depth of tree by one. */
			Assert(fpm->btree_depth > 0);
			--fpm->btree_depth;
			if (root->hdr.magic == FREE_PAGE_LEAF_MAGIC)
			{
				/* If root is a leaf, convert only entry to singleton range. */
				relptr_store(base, fpm->btree_root, (FreePageBtree *) NULL);
				fpm->singleton_first_page = root->u.leaf_key[0].first_page;
				fpm->singleton_npages = root->u.leaf_key[0].npages;
			}
			else
			{
				FreePageBtree *newroot;

				/* If root is an internal page, make only child the root. */
				Assert(root->hdr.magic == FREE_PAGE_INTERNAL_MAGIC);
				relptr_copy(fpm->btree_root, root->u.internal_key[0].child);
				newroot = relptr_access(base, fpm->btree_root);
				relptr_store(base, newroot->hdr.parent, (FreePageBtree *) NULL);
			}
			FreePageBtreeRecycle(fpm, fpm_pointer_to_page(base, root));
		}
		else if (root->hdr.nused == 2 &&
				 root->hdr.magic == FREE_PAGE_LEAF_MAGIC)
		{
			Size		end_of_first;
			Size		start_of_second;

			end_of_first = root->u.leaf_key[0].first_page +
				root->u.leaf_key[0].npages;
			start_of_second = root->u.leaf_key[1].first_page;

			if (end_of_first + 1 == start_of_second)
			{
				Size		root_page = fpm_pointer_to_page(base, root);

				if (end_of_first == root_page)
				{
					FreePagePopSpanLeader(fpm, root->u.leaf_key[0].first_page);
					FreePagePopSpanLeader(fpm, root->u.leaf_key[1].first_page);
					fpm->singleton_first_page = root->u.leaf_key[0].first_page;
					fpm->singleton_npages = root->u.leaf_key[0].npages +
						root->u.leaf_key[1].npages + 1;
					fpm->btree_depth = 0;
					relptr_store(base, fpm->btree_root,
								 (FreePageBtree *) NULL);
					FreePagePushSpanLeader(fpm, fpm->singleton_first_page,
										   fpm->singleton_npages);
					Assert(max_contiguous_pages == 0);
					max_contiguous_pages = fpm->singleton_npages;
				}
			}

			/* Whether it worked or not, it's time to stop. */
			break;
		}
		else
		{
			/* Nothing more to do.  Stop. */
			break;
		}
	}

	/*
	 * Attempt to free recycled btree pages.  We skip this if releasing the
	 * recycled page would require a btree page split, because the page we're
	 * trying to recycle would be consumed by the split, which would be
	 * counterproductive.
	 *
	 * We also currently only ever attempt to recycle the first page on the
	 * list; that could be made more aggressive, but it's not clear that the
	 * complexity would be worthwhile.
	 */
	while (fpm->btree_recycle_count > 0)
	{
		FreePageBtree *btp;
		Size		first_page;
		Size		contiguous_pages;

		btp = FreePageBtreeGetRecycled(fpm);
		first_page = fpm_pointer_to_page(base, btp);
		contiguous_pages = FreePageManagerPutInternal(fpm, first_page, 1, true);
		if (contiguous_pages == 0)
		{
			FreePageBtreeRecycle(fpm, first_page);
			break;
		}
		else
		{
			if (contiguous_pages > max_contiguous_pages)
				max_contiguous_pages = contiguous_pages;
		}
	}

	return max_contiguous_pages;
}