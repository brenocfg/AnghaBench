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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_2__ {int s_clustersize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PageError (struct page*) ; 
 int filemap_fdatawrite_range (int /*<<< orphan*/ ,int,int) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int ocfs2_cow_sync_writeback(struct super_block *sb,
			     struct inode *inode,
			     u32 cpos, u32 num_clusters)
{
	int ret = 0;
	loff_t offset, end, map_end;
	pgoff_t page_index;
	struct page *page;

	if (ocfs2_should_order_data(inode))
		return 0;

	offset = ((loff_t)cpos) << OCFS2_SB(sb)->s_clustersize_bits;
	end = offset + (num_clusters << OCFS2_SB(sb)->s_clustersize_bits);

	ret = filemap_fdatawrite_range(inode->i_mapping,
				       offset, end - 1);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	while (offset < end) {
		page_index = offset >> PAGE_SHIFT;
		map_end = ((loff_t)page_index + 1) << PAGE_SHIFT;
		if (map_end > end)
			map_end = end;

		page = find_or_create_page(inode->i_mapping,
					   page_index, GFP_NOFS);
		BUG_ON(!page);

		wait_on_page_writeback(page);
		if (PageError(page)) {
			ret = -EIO;
			mlog_errno(ret);
		} else
			mark_page_accessed(page);

		unlock_page(page);
		put_page(page);
		page = NULL;
		offset = map_end;
		if (ret)
			break;
	}

	return ret;
}