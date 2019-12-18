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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct ocfs2_write_ctxt {struct page* w_target_page; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_page_regions (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_figure_cluster_boundaries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int ocfs2_map_page_blocks (struct page*,int /*<<< orphan*/ *,struct inode*,unsigned int,unsigned int,int) ; 
 int page_offset (struct page*) ; 

__attribute__((used)) static int ocfs2_prepare_page_for_write(struct inode *inode, u64 *p_blkno,
					struct ocfs2_write_ctxt *wc,
					struct page *page, u32 cpos,
					loff_t user_pos, unsigned user_len,
					int new)
{
	int ret;
	unsigned int map_from = 0, map_to = 0;
	unsigned int cluster_start, cluster_end;
	unsigned int user_data_from = 0, user_data_to = 0;

	ocfs2_figure_cluster_boundaries(OCFS2_SB(inode->i_sb), cpos,
					&cluster_start, &cluster_end);

	/* treat the write as new if the a hole/lseek spanned across
	 * the page boundary.
	 */
	new = new | ((i_size_read(inode) <= page_offset(page)) &&
			(page_offset(page) <= user_pos));

	if (page == wc->w_target_page) {
		map_from = user_pos & (PAGE_SIZE - 1);
		map_to = map_from + user_len;

		if (new)
			ret = ocfs2_map_page_blocks(page, p_blkno, inode,
						    cluster_start, cluster_end,
						    new);
		else
			ret = ocfs2_map_page_blocks(page, p_blkno, inode,
						    map_from, map_to, new);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		user_data_from = map_from;
		user_data_to = map_to;
		if (new) {
			map_from = cluster_start;
			map_to = cluster_end;
		}
	} else {
		/*
		 * If we haven't allocated the new page yet, we
		 * shouldn't be writing it out without copying user
		 * data. This is likely a math error from the caller.
		 */
		BUG_ON(!new);

		map_from = cluster_start;
		map_to = cluster_end;

		ret = ocfs2_map_page_blocks(page, p_blkno, inode,
					    cluster_start, cluster_end, new);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	/*
	 * Parts of newly allocated pages need to be zero'd.
	 *
	 * Above, we have also rewritten 'to' and 'from' - as far as
	 * the rest of the function is concerned, the entire cluster
	 * range inside of a page needs to be written.
	 *
	 * We can skip this if the page is up to date - it's already
	 * been zero'd from being read in as a hole.
	 */
	if (new && !PageUptodate(page))
		ocfs2_clear_page_regions(page, OCFS2_SB(inode->i_sb),
					 cpos, user_data_from, user_data_to);

	flush_dcache_page(page);

out:
	return ret;
}