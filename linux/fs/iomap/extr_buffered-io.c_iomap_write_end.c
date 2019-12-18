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
struct iomap_page_ops {int /*<<< orphan*/  (* page_done ) (struct inode*,scalar_t__,int,struct page*,struct iomap*) ;} ;
struct iomap {scalar_t__ type; int flags; struct iomap_page_ops* page_ops; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mapping; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int IOMAP_F_BUFFER_HEAD ; 
 int IOMAP_F_SIZE_CHANGED ; 
 scalar_t__ IOMAP_INLINE ; 
 int __iomap_write_end (struct inode*,scalar_t__,unsigned int,unsigned int,struct page*,struct iomap*) ; 
 int block_write_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int iomap_write_end_inline (struct inode*,struct page*,struct iomap*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  iomap_write_failed (struct inode*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pagecache_isize_extended (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct inode*,scalar_t__,int,struct page*,struct iomap*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
iomap_write_end(struct inode *inode, loff_t pos, unsigned len,
		unsigned copied, struct page *page, struct iomap *iomap)
{
	const struct iomap_page_ops *page_ops = iomap->page_ops;
	loff_t old_size = inode->i_size;
	int ret;

	if (iomap->type == IOMAP_INLINE) {
		ret = iomap_write_end_inline(inode, page, iomap, pos, copied);
	} else if (iomap->flags & IOMAP_F_BUFFER_HEAD) {
		ret = block_write_end(NULL, inode->i_mapping, pos, len, copied,
				page, NULL);
	} else {
		ret = __iomap_write_end(inode, pos, len, copied, page, iomap);
	}

	/*
	 * Update the in-memory inode size after copying the data into the page
	 * cache.  It's up to the file system to write the updated size to disk,
	 * preferably after I/O completion so that no stale data is exposed.
	 */
	if (pos + ret > old_size) {
		i_size_write(inode, pos + ret);
		iomap->flags |= IOMAP_F_SIZE_CHANGED;
	}
	unlock_page(page);

	if (old_size < pos)
		pagecache_isize_extended(inode, old_size, pos);
	if (page_ops && page_ops->page_done)
		page_ops->page_done(inode, pos, ret, page, iomap);
	put_page(page);

	if (ret < len)
		iomap_write_failed(inode, pos, len);
	return ret;
}