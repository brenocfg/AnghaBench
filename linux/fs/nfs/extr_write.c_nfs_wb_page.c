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
struct writeback_control {scalar_t__ range_end; scalar_t__ range_start; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_SYNC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int nfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_writepage_locked (struct page*,struct writeback_control*) ; 
 scalar_t__ page_file_offset (struct page*) ; 
 int /*<<< orphan*/  trace_nfs_writeback_page_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_writeback_page_exit (struct inode*,int) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int nfs_wb_page(struct inode *inode, struct page *page)
{
	loff_t range_start = page_file_offset(page);
	loff_t range_end = range_start + (loff_t)(PAGE_SIZE - 1);
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = 0,
		.range_start = range_start,
		.range_end = range_end,
	};
	int ret;

	trace_nfs_writeback_page_enter(inode);

	for (;;) {
		wait_on_page_writeback(page);
		if (clear_page_dirty_for_io(page)) {
			ret = nfs_writepage_locked(page, &wbc);
			if (ret < 0)
				goto out_error;
			continue;
		}
		ret = 0;
		if (!PagePrivate(page))
			break;
		ret = nfs_commit_inode(inode, FLUSH_SYNC);
		if (ret < 0)
			goto out_error;
	}
out_error:
	trace_nfs_writeback_page_exit(inode, ret);
	return ret;
}