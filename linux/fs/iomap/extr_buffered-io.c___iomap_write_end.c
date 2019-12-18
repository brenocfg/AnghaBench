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
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  iomap_set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  iomap_set_range_uptodate (struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
__iomap_write_end(struct inode *inode, loff_t pos, unsigned len,
		unsigned copied, struct page *page, struct iomap *iomap)
{
	flush_dcache_page(page);

	/*
	 * The blocks that were entirely written will now be uptodate, so we
	 * don't have to worry about a readpage reading them and overwriting a
	 * partial write.  However if we have encountered a short write and only
	 * partially written into a block, it will not be marked uptodate, so a
	 * readpage might come in and destroy our partial write.
	 *
	 * Do the simplest thing, and just treat any short write to a non
	 * uptodate page as a zero-length write, and force the caller to redo
	 * the whole thing.
	 */
	if (unlikely(copied < len && !PageUptodate(page)))
		return 0;
	iomap_set_range_uptodate(page, offset_in_page(pos), len);
	iomap_set_page_dirty(page);
	return copied;
}