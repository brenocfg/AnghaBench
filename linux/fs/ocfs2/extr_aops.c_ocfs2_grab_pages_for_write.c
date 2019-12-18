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
typedef  int /*<<< orphan*/  u32 ;
struct page {struct address_space* mapping; } ;
struct ocfs2_write_ctxt {unsigned long w_num_pages; scalar_t__ w_type; int w_target_locked; struct page** w_pages; struct page* w_target_page; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ OCFS2_WRITE_DIRECT ; 
 scalar_t__ OCFS2_WRITE_MMAP ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (struct address_space*) ; 
 struct page* find_or_create_page (struct address_space*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned long ocfs2_align_clusters_to_page_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ocfs2_pages_per_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

__attribute__((used)) static int ocfs2_grab_pages_for_write(struct address_space *mapping,
				      struct ocfs2_write_ctxt *wc,
				      u32 cpos, loff_t user_pos,
				      unsigned user_len, int new,
				      struct page *mmap_page)
{
	int ret = 0, i;
	unsigned long start, target_index, end_index, index;
	struct inode *inode = mapping->host;
	loff_t last_byte;

	target_index = user_pos >> PAGE_SHIFT;

	/*
	 * Figure out how many pages we'll be manipulating here. For
	 * non allocating write, we just change the one
	 * page. Otherwise, we'll need a whole clusters worth.  If we're
	 * writing past i_size, we only need enough pages to cover the
	 * last page of the write.
	 */
	if (new) {
		wc->w_num_pages = ocfs2_pages_per_cluster(inode->i_sb);
		start = ocfs2_align_clusters_to_page_index(inode->i_sb, cpos);
		/*
		 * We need the index *past* the last page we could possibly
		 * touch.  This is the page past the end of the write or
		 * i_size, whichever is greater.
		 */
		last_byte = max(user_pos + user_len, i_size_read(inode));
		BUG_ON(last_byte < 1);
		end_index = ((last_byte - 1) >> PAGE_SHIFT) + 1;
		if ((start + wc->w_num_pages) > end_index)
			wc->w_num_pages = end_index - start;
	} else {
		wc->w_num_pages = 1;
		start = target_index;
	}
	end_index = (user_pos + user_len - 1) >> PAGE_SHIFT;

	for(i = 0; i < wc->w_num_pages; i++) {
		index = start + i;

		if (index >= target_index && index <= end_index &&
		    wc->w_type == OCFS2_WRITE_MMAP) {
			/*
			 * ocfs2_pagemkwrite() is a little different
			 * and wants us to directly use the page
			 * passed in.
			 */
			lock_page(mmap_page);

			/* Exit and let the caller retry */
			if (mmap_page->mapping != mapping) {
				WARN_ON(mmap_page->mapping);
				unlock_page(mmap_page);
				ret = -EAGAIN;
				goto out;
			}

			get_page(mmap_page);
			wc->w_pages[i] = mmap_page;
			wc->w_target_locked = true;
		} else if (index >= target_index && index <= end_index &&
			   wc->w_type == OCFS2_WRITE_DIRECT) {
			/* Direct write has no mapping page. */
			wc->w_pages[i] = NULL;
			continue;
		} else {
			wc->w_pages[i] = find_or_create_page(mapping, index,
							     GFP_NOFS);
			if (!wc->w_pages[i]) {
				ret = -ENOMEM;
				mlog_errno(ret);
				goto out;
			}
		}
		wait_for_stable_page(wc->w_pages[i]);

		if (index == target_index)
			wc->w_target_page = wc->w_pages[i];
	}
out:
	if (ret)
		wc->w_target_locked = false;
	return ret;
}