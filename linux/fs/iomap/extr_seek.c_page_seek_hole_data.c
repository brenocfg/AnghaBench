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
struct page {TYPE_1__* mapping; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct address_space_operations {int (* is_partially_uptodate ) (struct page*,unsigned int,unsigned int) ;} ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct address_space_operations* a_ops; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int PageUptodate (struct page*) ; 
 int SEEK_DATA ; 
 int SEEK_HOLE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 unsigned int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 unsigned int offset_in_page (scalar_t__) ; 
 scalar_t__ page_offset (struct page*) ; 
 int stub1 (struct page*,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static bool
page_seek_hole_data(struct inode *inode, struct page *page, loff_t *lastoff,
		int whence)
{
	const struct address_space_operations *ops = inode->i_mapping->a_ops;
	unsigned int bsize = i_blocksize(inode), off;
	bool seek_data = whence == SEEK_DATA;
	loff_t poff = page_offset(page);

	if (WARN_ON_ONCE(*lastoff >= poff + PAGE_SIZE))
		return false;

	if (*lastoff < poff) {
		/*
		 * Last offset smaller than the start of the page means we found
		 * a hole:
		 */
		if (whence == SEEK_HOLE)
			return true;
		*lastoff = poff;
	}

	/*
	 * Just check the page unless we can and should check block ranges:
	 */
	if (bsize == PAGE_SIZE || !ops->is_partially_uptodate)
		return PageUptodate(page) == seek_data;

	lock_page(page);
	if (unlikely(page->mapping != inode->i_mapping))
		goto out_unlock_not_found;

	for (off = 0; off < PAGE_SIZE; off += bsize) {
		if (offset_in_page(*lastoff) >= off + bsize)
			continue;
		if (ops->is_partially_uptodate(page, off, bsize) == seek_data) {
			unlock_page(page);
			return true;
		}
		*lastoff = poff + off + bsize;
	}

out_unlock_not_found:
	unlock_page(page);
	return false;
}