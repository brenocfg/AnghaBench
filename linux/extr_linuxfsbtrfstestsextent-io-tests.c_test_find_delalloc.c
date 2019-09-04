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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct extent_io_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int PROCESS_RELEASE ; 
 int PROCESS_TEST_LOCKED ; 
 int PROCESS_UNLOCK ; 
 unsigned long SZ_128M ; 
 unsigned long SZ_1M ; 
 unsigned long SZ_256M ; 
 unsigned long SZ_64M ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 struct inode* btrfs_new_test_inode () ; 
 int /*<<< orphan*/  clear_extent_bits (struct extent_io_tree*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  extent_io_tree_init (struct extent_io_tree*,struct inode*) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long find_lock_delalloc_range (struct inode*,struct extent_io_tree*,struct page*,unsigned long*,unsigned long*,unsigned long) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,unsigned long) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ process_page_range (struct inode*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_extent_delalloc (struct extent_io_tree*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  unlock_extent (struct extent_io_tree*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int test_find_delalloc(u32 sectorsize)
{
	struct inode *inode;
	struct extent_io_tree tmp;
	struct page *page;
	struct page *locked_page = NULL;
	unsigned long index = 0;
	u64 total_dirty = SZ_256M;
	u64 max_bytes = SZ_128M;
	u64 start, end, test_start;
	u64 found;
	int ret = -EINVAL;

	test_msg("running find delalloc tests");

	inode = btrfs_new_test_inode();
	if (!inode) {
		test_err("failed to allocate test inode");
		return -ENOMEM;
	}

	extent_io_tree_init(&tmp, inode);

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
	set_extent_delalloc(&tmp, 0, sectorsize - 1, 0, NULL);
	start = 0;
	end = 0;
	found = find_lock_delalloc_range(inode, &tmp, locked_page, &start,
					 &end, max_bytes);
	if (!found) {
		test_err("should have found at least one delalloc");
		goto out_bits;
	}
	if (start != 0 || end != (sectorsize - 1)) {
		test_err("expected start 0 end %u, got start %llu end %llu",
			sectorsize - 1, start, end);
		goto out_bits;
	}
	unlock_extent(&tmp, start, end);
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
	set_extent_delalloc(&tmp, sectorsize, max_bytes - 1, 0, NULL);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, &tmp, locked_page, &start,
					 &end, max_bytes);
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
	unlock_extent(&tmp, start, end);
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
	found = find_lock_delalloc_range(inode, &tmp, locked_page, &start,
					 &end, max_bytes);
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
	set_extent_delalloc(&tmp, max_bytes, total_dirty - 1, 0, NULL);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, &tmp, locked_page, &start,
					 &end, max_bytes);
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
	unlock_extent(&tmp, start, end);

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
	found = find_lock_delalloc_range(inode, &tmp, locked_page, &start,
					 &end, max_bytes);
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
	clear_extent_bits(&tmp, 0, total_dirty - 1, (unsigned)-1);
out:
	if (locked_page)
		put_page(locked_page);
	process_page_range(inode, 0, total_dirty - 1,
			   PROCESS_UNLOCK | PROCESS_RELEASE);
	iput(inode);
	return ret;
}