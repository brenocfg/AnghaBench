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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ nr_to_write; } ;
struct pagevec {struct page** pages; } ;
struct page {scalar_t__ mapping; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * wb_sync_req; } ;
typedef  scalar_t__ pgoff_t ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_DNODE (struct page*) ; 
 scalar_t__ IS_INODE (struct page*) ; 
 size_t NODE ; 
 scalar_t__ NODE_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ WB_SYNC_NONE ; 
 int __write_node_page (struct page*,int,int*,struct writeback_control*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inline_node (struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,size_t) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,size_t,int,int) ; 
 scalar_t__ flush_dirty_inode (struct page*) ; 
 int /*<<< orphan*/  flush_inline_data (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 scalar_t__ is_cold_node (struct page*) ; 
 scalar_t__ is_inline_node (struct page*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int pagevec_lookup_tag (struct pagevec*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  set_dentry_mark (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fsync_mark (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int f2fs_sync_node_pages(struct f2fs_sb_info *sbi,
				struct writeback_control *wbc,
				bool do_balance, enum iostat_type io_type)
{
	pgoff_t index;
	struct pagevec pvec;
	int step = 0;
	int nwritten = 0;
	int ret = 0;
	int nr_pages, done = 0;

	pagevec_init(&pvec);

next_step:
	index = 0;

	while (!done && (nr_pages = pagevec_lookup_tag(&pvec,
			NODE_MAPPING(sbi), &index, PAGECACHE_TAG_DIRTY))) {
		int i;

		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];
			bool submitted = false;
			bool may_dirty = true;

			/* give a priority to WB_SYNC threads */
			if (atomic_read(&sbi->wb_sync_req[NODE]) &&
					wbc->sync_mode == WB_SYNC_NONE) {
				done = 1;
				break;
			}

			/*
			 * flushing sequence with step:
			 * 0. indirect nodes
			 * 1. dentry dnodes
			 * 2. file dnodes
			 */
			if (step == 0 && IS_DNODE(page))
				continue;
			if (step == 1 && (!IS_DNODE(page) ||
						is_cold_node(page)))
				continue;
			if (step == 2 && (!IS_DNODE(page) ||
						!is_cold_node(page)))
				continue;
lock_node:
			if (wbc->sync_mode == WB_SYNC_ALL)
				lock_page(page);
			else if (!trylock_page(page))
				continue;

			if (unlikely(page->mapping != NODE_MAPPING(sbi))) {
continue_unlock:
				unlock_page(page);
				continue;
			}

			if (!PageDirty(page)) {
				/* someone wrote it for us */
				goto continue_unlock;
			}

			/* flush inline_data */
			if (is_inline_node(page)) {
				clear_inline_node(page);
				unlock_page(page);
				flush_inline_data(sbi, ino_of_node(page));
				goto lock_node;
			}

			/* flush dirty inode */
			if (IS_INODE(page) && may_dirty) {
				may_dirty = false;
				if (flush_dirty_inode(page))
					goto lock_node;
			}

			f2fs_wait_on_page_writeback(page, NODE, true, true);

			if (!clear_page_dirty_for_io(page))
				goto continue_unlock;

			set_fsync_mark(page, 0);
			set_dentry_mark(page, 0);

			ret = __write_node_page(page, false, &submitted,
						wbc, do_balance, io_type, NULL);
			if (ret)
				unlock_page(page);
			else if (submitted)
				nwritten++;

			if (--wbc->nr_to_write == 0)
				break;
		}
		pagevec_release(&pvec);
		cond_resched();

		if (wbc->nr_to_write == 0) {
			step = 2;
			break;
		}
	}

	if (step < 2) {
		if (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
				wbc->sync_mode == WB_SYNC_NONE && step == 1)
			goto out;
		step++;
		goto next_step;
	}
out:
	if (nwritten)
		f2fs_submit_merged_write(sbi, NODE);

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	return ret;
}