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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; struct super_block* i_sb; } ;
struct address_space {int dummy; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int s_clustersize_bits; int s_clustersize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int block_read_full_page (struct page*,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (struct address_space*,int,int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_cow_buffer ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,int) ; 
 int /*<<< orphan*/  ocfs2_get_block ; 
 int /*<<< orphan*/  ocfs2_map_and_dirty_page (struct inode*,int /*<<< orphan*/ *,unsigned int,unsigned int,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_ocfs2_duplicate_clusters_by_page (int,int,int,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int*,int /*<<< orphan*/ ) ; 
 int write_one_page (struct page*) ; 

int ocfs2_duplicate_clusters_by_page(handle_t *handle,
				     struct inode *inode,
				     u32 cpos, u32 old_cluster,
				     u32 new_cluster, u32 new_len)
{
	int ret = 0, partial;
	struct super_block *sb = inode->i_sb;
	u64 new_block = ocfs2_clusters_to_blocks(sb, new_cluster);
	struct page *page;
	pgoff_t page_index;
	unsigned int from, to;
	loff_t offset, end, map_end;
	struct address_space *mapping = inode->i_mapping;

	trace_ocfs2_duplicate_clusters_by_page(cpos, old_cluster,
					       new_cluster, new_len);

	offset = ((loff_t)cpos) << OCFS2_SB(sb)->s_clustersize_bits;
	end = offset + (new_len << OCFS2_SB(sb)->s_clustersize_bits);
	/*
	 * We only duplicate pages until we reach the page contains i_size - 1.
	 * So trim 'end' to i_size.
	 */
	if (end > i_size_read(inode))
		end = i_size_read(inode);

	while (offset < end) {
		page_index = offset >> PAGE_SHIFT;
		map_end = ((loff_t)page_index + 1) << PAGE_SHIFT;
		if (map_end > end)
			map_end = end;

		/* from, to is the offset within the page. */
		from = offset & (PAGE_SIZE - 1);
		to = PAGE_SIZE;
		if (map_end & (PAGE_SIZE - 1))
			to = map_end & (PAGE_SIZE - 1);

retry:
		page = find_or_create_page(mapping, page_index, GFP_NOFS);
		if (!page) {
			ret = -ENOMEM;
			mlog_errno(ret);
			break;
		}

		/*
		 * In case PAGE_SIZE <= CLUSTER_SIZE, we do not expect a dirty
		 * page, so write it back.
		 */
		if (PAGE_SIZE <= OCFS2_SB(sb)->s_clustersize) {
			if (PageDirty(page)) {
				/*
				 * write_on_page will unlock the page on return
				 */
				ret = write_one_page(page);
				goto retry;
			}
		}

		if (!PageUptodate(page)) {
			ret = block_read_full_page(page, ocfs2_get_block);
			if (ret) {
				mlog_errno(ret);
				goto unlock;
			}
			lock_page(page);
		}

		if (page_has_buffers(page)) {
			ret = walk_page_buffers(handle, page_buffers(page),
						from, to, &partial,
						ocfs2_clear_cow_buffer);
			if (ret) {
				mlog_errno(ret);
				goto unlock;
			}
		}

		ocfs2_map_and_dirty_page(inode,
					 handle, from, to,
					 page, 0, &new_block);
		mark_page_accessed(page);
unlock:
		unlock_page(page);
		put_page(page);
		page = NULL;
		offset = map_end;
		if (ret)
			break;
	}

	return ret;
}