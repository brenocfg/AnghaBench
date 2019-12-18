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
struct ocfs2_write_ctxt {int w_num_pages; int /*<<< orphan*/  w_handle; struct page** w_pages; scalar_t__ w_target_page; } ;
struct inode {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  block_commit_write (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_jbd2_inode_add_write (int /*<<< orphan*/ ,struct inode*,int,unsigned int) ; 
 scalar_t__ ocfs2_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_zero_new_buffers (scalar_t__,unsigned int,unsigned int) ; 
 scalar_t__ page_has_buffers (struct page*) ; 

__attribute__((used)) static void ocfs2_write_failure(struct inode *inode,
				struct ocfs2_write_ctxt *wc,
				loff_t user_pos, unsigned user_len)
{
	int i;
	unsigned from = user_pos & (PAGE_SIZE - 1),
		to = user_pos + user_len;
	struct page *tmppage;

	if (wc->w_target_page)
		ocfs2_zero_new_buffers(wc->w_target_page, from, to);

	for(i = 0; i < wc->w_num_pages; i++) {
		tmppage = wc->w_pages[i];

		if (tmppage && page_has_buffers(tmppage)) {
			if (ocfs2_should_order_data(inode))
				ocfs2_jbd2_inode_add_write(wc->w_handle, inode,
							   user_pos, user_len);

			block_commit_write(tmppage, from, to);
		}
	}
}