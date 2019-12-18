#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_2__ {struct extent_io_tree io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_MAX_EXTENT_SIZE ; 
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IO_TREE_SELFTEST ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PROCESS_RELEASE ; 
 int PROCESS_TEST_LOCKED ; 
 int PROCESS_UNLOCK ; 
 int SZ_1M ; 
 int SZ_64M ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  TEST_ALLOC_INODE ; 
 struct inode* btrfs_new_test_inode () ; 
 int /*<<< orphan*/  clear_extent_bits (struct extent_io_tree*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  extent_io_tree_init (int /*<<< orphan*/ *,struct extent_io_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int) ; 
 int find_lock_delalloc_range (struct inode*,struct page*,int*,int*) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,int) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ process_page_range (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_extent_delalloc (struct extent_io_tree*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_extent (struct extent_io_tree*,int,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int test_find_delalloc(u32 sectorsize)
{
	struct inode *inode;
	struct extent_io_tree *tmp;
	struct page *page;
	struct page *locked_page = NULL;
	unsigned long index = 0;
	/* In this test we need at least 2 file extents at its maximum size */
	u64 max_bytes = BTRFS_MAX_EXTENT_SIZE;
	u64 total_dirty = 2 * max_bytes;
	u64 start, end, test_start;
	bool found;
	int ret = -EINVAL;

	test_msg("running find delalloc tests");

	inode = btrfs_new_test_inode();
	if (!inode) {
		test_std_err(TEST_ALLOC_INODE);
		return -ENOMEM;
	}
	tmp = &BTRFS_I(inode)->io_tree;

	/*
	 * Passing NULL as we don't have fs_info but tracepoints are not used
	 * at this point
	 */
	extent_io_tree_init(NULL, tmp, IO_TREE_SELFTEST, NULL);

	/*
	 * First go through and create and mark all of our pages dirty, we pin
	 * everything to make sure our pages don't get evicted and screw up our
	 * test.
	 */
	for (index = 0; index < (total_dirty >> PAGE_SHIFT); index++) {
		page = find_or_create_page(inode->i_mapping, index, GFP_KERNEL);
		if (!page) {
			test_err("failed to allocate test page");
			ret = -ENOMEM;
			goto out;
		}
		SetPageDirty(page);
		if (index) {
			unlock_page(page);
		} else {
			get_page(page);
			locked_page = page;
		}
	}

	/* Test this scenario
	 * |--- delalloc ---|
	 * |---  search  ---|
	 */
	set_extent_delalloc(tmp, 0, sectorsize - 1, 0, NULL);
	start = 0;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	if (!found) {
		test_err("should have found at least one delalloc");
		goto out_bits;
	}
	if (start != 0 || end != (sectorsize - 1)) {
		test_err("expected start 0 end %u, got start %llu end %llu",
			sectorsize - 1, start, end);
		goto out_bits;
	}
	unlock_extent(tmp, start, end);
	unlock_page(locked_page);
	put_page(locked_page);

	/*
	 * Test this scenario
	 *
	 * |--- delalloc ---|
	 *           |--- search ---|
	 */
	test_start = SZ_64M;
	locked_page = find_lock_page(inode->i_mapping,
				     test_start >> PAGE_SHIFT);
	if (!locked_page) {
		test_err("couldn't find the locked page");
		goto out_bits;
	}
	set_extent_delalloc(tmp, sectorsize, max_bytes - 1, 0, NULL);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	if (!found) {
		test_err("couldn't find delalloc in our range");
		goto out_bits;
	}
	if (start != test_start || end != max_bytes - 1) {
		test_err("expected start %llu end %llu, got start %llu, end %llu",
				test_start, max_bytes - 1, start, end);
		goto out_bits;
	}
	if (process_page_range(inode, start, end,
			       PROCESS_TEST_LOCKED | PROCESS_UNLOCK)) {
		test_err("there were unlocked pages in the range");
		goto out_bits;
	}
	unlock_extent(tmp, start, end);
	/* locked_page was unlocked above */
	put_page(locked_page);

	/*
	 * Test this scenario
	 * |--- delalloc ---|
	 *                    |--- search ---|
	 */
	test_start = max_bytes + sectorsize;
	locked_page = find_lock_page(inode->i_mapping, test_start >>
				     PAGE_SHIFT);
	if (!locked_page) {
		test_err("couldn't find the locked page");
		goto out_bits;
	}
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	if (found) {
		test_err("found range when we shouldn't have");
		goto out_bits;
	}
	if (end != (u64)-1) {
		test_err("did not return the proper end offset");
		goto out_bits;
	}

	/*
	 * Test this scenario
	 * [------- delalloc -------|
	 * [max_bytes]|-- search--|
	 *
	 * We are re-using our test_start from above since it works out well.
	 */
	set_extent_delalloc(tmp, max_bytes, total_dirty - 1, 0, NULL);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	if (!found) {
		test_err("didn't find our range");
		goto out_bits;
	}
	if (start != test_start || end != total_dirty - 1) {
		test_err("expected start %llu end %llu, got start %llu end %llu",
			 test_start, total_dirty - 1, start, end);
		goto out_bits;
	}
	if (process_page_range(inode, start, end,
			       PROCESS_TEST_LOCKED | PROCESS_UNLOCK)) {
		test_err("pages in range were not all locked");
		goto out_bits;
	}
	unlock_extent(tmp, start, end);

	/*
	 * Now to test where we run into a page that is no longer dirty in the
	 * range we want to find.
	 */
	page = find_get_page(inode->i_mapping,
			     (max_bytes + SZ_1M) >> PAGE_SHIFT);
	if (!page) {
		test_err("couldn't find our page");
		goto out_bits;
	}
	ClearPageDirty(page);
	put_page(page);

	/* We unlocked it in the previous test */
	lock_page(locked_page);
	start = test_start;
	end = 0;
	/*
	 * Currently if we fail to find dirty pages in the delalloc range we
	 * will adjust max_bytes down to PAGE_SIZE and then re-search.  If
	 * this changes at any point in the future we will need to fix this
	 * tests expected behavior.
	 */
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	if (!found) {
		test_err("didn't find our range");
		goto out_bits;
	}
	if (start != test_start && end != test_start + PAGE_SIZE - 1) {
		test_err("expected start %llu end %llu, got start %llu end %llu",
			 test_start, test_start + PAGE_SIZE - 1, start, end);
		goto out_bits;
	}
	if (process_page_range(inode, start, end, PROCESS_TEST_LOCKED |
			       PROCESS_UNLOCK)) {
		test_err("pages in range were not all locked");
		goto out_bits;
	}
	ret = 0;
out_bits:
	clear_extent_bits(tmp, 0, total_dirty - 1, (unsigned)-1);
out:
	if (locked_page)
		put_page(locked_page);
	process_page_range(inode, 0, total_dirty - 1,
			   PROCESS_UNLOCK | PROCESS_RELEASE);
	iput(inode);
	return ret;
}