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
typedef  unsigned long u64 ;
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct TYPE_2__ {unsigned int sb_bsize; unsigned long sb_bsize_shift; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; struct inode i_inode; } ;
struct buffer_head {int /*<<< orphan*/  b_size; struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (struct address_space*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  gfs2_block_map (struct inode*,unsigned long,struct buffer_head*,int) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_ordered_add_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_data (int /*<<< orphan*/ ,struct buffer_head*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,int,struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_write_buf_to_page(struct gfs2_inode *ip, unsigned long index,
				  unsigned off, void *buf, unsigned bytes)
{
	struct inode *inode = &ip->i_inode;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct address_space *mapping = inode->i_mapping;
	struct page *page;
	struct buffer_head *bh;
	void *kaddr;
	u64 blk;
	unsigned bsize = sdp->sd_sb.sb_bsize, bnum = 0, boff = 0;
	unsigned to_write = bytes, pg_off = off;
	int done = 0;

	blk = index << (PAGE_SHIFT - sdp->sd_sb.sb_bsize_shift);
	boff = off % bsize;

	page = find_or_create_page(mapping, index, GFP_NOFS);
	if (!page)
		return -ENOMEM;
	if (!page_has_buffers(page))
		create_empty_buffers(page, bsize, 0);

	bh = page_buffers(page);
	while (!done) {
		/* Find the beginning block within the page */
		if (pg_off >= ((bnum * bsize) + bsize)) {
			bh = bh->b_this_page;
			bnum++;
			blk++;
			continue;
		}
		if (!buffer_mapped(bh)) {
			gfs2_block_map(inode, blk, bh, 1);
			if (!buffer_mapped(bh))
				goto unlock_out;
			/* If it's a newly allocated disk block, zero it */
			if (buffer_new(bh))
				zero_user(page, bnum * bsize, bh->b_size);
		}
		if (PageUptodate(page))
			set_buffer_uptodate(bh);
		if (!buffer_uptodate(bh)) {
			ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1, &bh);
			wait_on_buffer(bh);
			if (!buffer_uptodate(bh))
				goto unlock_out;
		}
		if (gfs2_is_jdata(ip))
			gfs2_trans_add_data(ip->i_gl, bh);
		else
			gfs2_ordered_add_inode(ip);

		/* If we need to write to the next block as well */
		if (to_write > (bsize - boff)) {
			pg_off += (bsize - boff);
			to_write -= (bsize - boff);
			boff = pg_off % bsize;
			continue;
		}
		done = 1;
	}

	/* Write to the page, now that we have setup the buffer(s) */
	kaddr = kmap_atomic(page);
	memcpy(kaddr + off, buf, bytes);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);
	unlock_page(page);
	put_page(page);

	return 0;

unlock_out:
	unlock_page(page);
	put_page(page);
	return -EIO;
}