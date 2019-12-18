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
struct writeback_control {int /*<<< orphan*/  for_reclaim; } ;
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  FS_CP_META_IO ; 
 int /*<<< orphan*/  META ; 
 int /*<<< orphan*/  META_FLUSH ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __f2fs_write_meta_page (struct page*,struct writeback_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 scalar_t__ f2fs_cp_error (struct f2fs_sb_info*) ; 
 struct page* f2fs_grab_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void commit_checkpoint(struct f2fs_sb_info *sbi,
	void *src, block_t blk_addr)
{
	struct writeback_control wbc = {
		.for_reclaim = 0,
	};

	/*
	 * pagevec_lookup_tag and lock_page again will take
	 * some extra time. Therefore, f2fs_update_meta_pages and
	 * f2fs_sync_meta_pages are combined in this function.
	 */
	struct page *page = f2fs_grab_meta_page(sbi, blk_addr);
	int err;

	f2fs_wait_on_page_writeback(page, META, true, true);

	memcpy(page_address(page), src, PAGE_SIZE);

	set_page_dirty(page);
	if (unlikely(!clear_page_dirty_for_io(page)))
		f2fs_bug_on(sbi, 1);

	/* writeout cp pack 2 page */
	err = __f2fs_write_meta_page(page, &wbc, FS_CP_META_IO);
	if (unlikely(err && f2fs_cp_error(sbi))) {
		f2fs_put_page(page, 1);
		return;
	}

	f2fs_bug_on(sbi, err);
	f2fs_put_page(page, 0);

	/* submit checkpoint (with barrier if NOBARRIER is not set) */
	f2fs_submit_merged_write(sbi, META_FLUSH);
}