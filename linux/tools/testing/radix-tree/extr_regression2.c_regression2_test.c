#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 int RADIX_TREE_MAP_SIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_tree ; 
 struct page* page_alloc () ; 
 int /*<<< orphan*/  printv (int,char*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radix_tree_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_gang_lookup_tag_slot (int /*<<< orphan*/ *,void***,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_tagged_items (int /*<<< orphan*/ *,unsigned long,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void regression2_test(void)
{
	int i;
	struct page *p;
	int max_slots = RADIX_TREE_MAP_SIZE;
	unsigned long int start, end;
	struct page *pages[1];

	printv(1, "running regression test 2 (should take milliseconds)\n");
	/* 0. */
	for (i = 0; i <= max_slots - 1; i++) {
		p = page_alloc();
		radix_tree_insert(&mt_tree, i, p);
	}
	radix_tree_tag_set(&mt_tree, max_slots - 1, PAGECACHE_TAG_DIRTY);

	/* 1. */
	start = 0;
	end = max_slots - 2;
	tag_tagged_items(&mt_tree, start, end, 1,
				PAGECACHE_TAG_DIRTY, PAGECACHE_TAG_TOWRITE);

	/* 2. */
	p = page_alloc();
	radix_tree_insert(&mt_tree, max_slots, p);

	/* 3. */
	radix_tree_tag_clear(&mt_tree, max_slots - 1, PAGECACHE_TAG_DIRTY);

	/* 4. */
	for (i = max_slots - 1; i >= 0; i--)
		free(radix_tree_delete(&mt_tree, i));

	/* 5. */
	// NOTE: start should not be 0 because radix_tree_gang_lookup_tag_slot
	//       can return.
	start = 1;
	end = max_slots - 2;
	radix_tree_gang_lookup_tag_slot(&mt_tree, (void ***)pages, start, end,
		PAGECACHE_TAG_TOWRITE);

	/* We remove all the remained nodes */
	free(radix_tree_delete(&mt_tree, max_slots));

	BUG_ON(!radix_tree_empty(&mt_tree));

	printv(1, "regression test 2, done\n");
}