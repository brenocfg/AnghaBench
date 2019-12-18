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
typedef  scalar_t__ u64 ;
struct page {scalar_t__ index; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_blkbits; int /*<<< orphan*/  i_mapping; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; struct inode i_inode; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Uptodate ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_max_stuffed_size (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_ordered_add_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_data (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int gfs2_unstuffer_page(struct gfs2_inode *ip, struct buffer_head *dibh,
			       u64 block, struct page *page)
{
	struct inode *inode = &ip->i_inode;
	struct buffer_head *bh;
	int release = 0;

	if (!page || page->index) {
		page = find_or_create_page(inode->i_mapping, 0, GFP_NOFS);
		if (!page)
			return -ENOMEM;
		release = 1;
	}

	if (!PageUptodate(page)) {
		void *kaddr = kmap(page);
		u64 dsize = i_size_read(inode);
 
		if (dsize > gfs2_max_stuffed_size(ip))
			dsize = gfs2_max_stuffed_size(ip);

		memcpy(kaddr, dibh->b_data + sizeof(struct gfs2_dinode), dsize);
		memset(kaddr + dsize, 0, PAGE_SIZE - dsize);
		kunmap(page);

		SetPageUptodate(page);
	}

	if (!page_has_buffers(page))
		create_empty_buffers(page, BIT(inode->i_blkbits),
				     BIT(BH_Uptodate));

	bh = page_buffers(page);

	if (!buffer_mapped(bh))
		map_bh(bh, inode->i_sb, block);

	set_buffer_uptodate(bh);
	if (gfs2_is_jdata(ip))
		gfs2_trans_add_data(ip->i_gl, bh);
	else {
		mark_buffer_dirty(bh);
		gfs2_ordered_add_inode(ip);
	}

	if (release) {
		unlock_page(page);
		put_page(page);
	}

	return 0;
}