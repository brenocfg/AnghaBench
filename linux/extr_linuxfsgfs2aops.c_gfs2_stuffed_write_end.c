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
typedef  unsigned int u64 ;
struct page {int dummy; } ;
struct inode {unsigned int i_size; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {unsigned char* b_data; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned int gfs2_max_stuffed_size (struct gfs2_inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int gfs2_stuffed_write_end(struct inode *inode, struct buffer_head *dibh,
			   loff_t pos, unsigned copied,
			   struct page *page)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	u64 to = pos + copied;
	void *kaddr;
	unsigned char *buf = dibh->b_data + sizeof(struct gfs2_dinode);

	BUG_ON(pos + copied > gfs2_max_stuffed_size(ip));

	kaddr = kmap_atomic(page);
	memcpy(buf + pos, kaddr + pos, copied);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);

	WARN_ON(!PageUptodate(page));
	unlock_page(page);
	put_page(page);

	if (copied) {
		if (inode->i_size < to)
			i_size_write(inode, to);
		mark_inode_dirty(inode);
	}
	return copied;
}