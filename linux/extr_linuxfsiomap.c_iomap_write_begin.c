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
struct iomap {unsigned int offset; unsigned int length; scalar_t__ type; int flags; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  unsigned int pgoff_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 int ENOMEM ; 
 int IOMAP_F_BUFFER_HEAD ; 
 scalar_t__ IOMAP_INLINE ; 
 unsigned int PAGE_SHIFT ; 
 int __block_write_begin_int (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ *,struct iomap*) ; 
 int __iomap_write_begin (struct inode*,unsigned int,unsigned int,struct page*,struct iomap*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 struct page* grab_cache_page_write_begin (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  iomap_read_inline_data (struct inode*,struct page*,struct iomap*) ; 
 int /*<<< orphan*/  iomap_write_failed (struct inode*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
iomap_write_begin(struct inode *inode, loff_t pos, unsigned len, unsigned flags,
		struct page **pagep, struct iomap *iomap)
{
	pgoff_t index = pos >> PAGE_SHIFT;
	struct page *page;
	int status = 0;

	BUG_ON(pos + len > iomap->offset + iomap->length);

	if (fatal_signal_pending(current))
		return -EINTR;

	page = grab_cache_page_write_begin(inode->i_mapping, index, flags);
	if (!page)
		return -ENOMEM;

	if (iomap->type == IOMAP_INLINE)
		iomap_read_inline_data(inode, page, iomap);
	else if (iomap->flags & IOMAP_F_BUFFER_HEAD)
		status = __block_write_begin_int(page, pos, len, NULL, iomap);
	else
		status = __iomap_write_begin(inode, pos, len, page, iomap);
	if (unlikely(status)) {
		unlock_page(page);
		put_page(page);
		page = NULL;

		iomap_write_failed(inode, pos, len);
	}

	*pagep = page;
	return status;
}