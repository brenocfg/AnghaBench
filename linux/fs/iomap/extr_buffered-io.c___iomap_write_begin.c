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
struct iomap_page {int dummy; } ;
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ PageUptodate (struct page*) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  iomap_adjust_read_range (struct inode*,struct iomap_page*,int*,int,unsigned int*,unsigned int*) ; 
 struct iomap_page* iomap_page_create (struct inode*,struct page*) ; 
 int iomap_read_page_sync (struct inode*,int,struct page*,unsigned int,unsigned int,unsigned int,unsigned int,struct iomap*) ; 
 unsigned int offset_in_page (int) ; 

__attribute__((used)) static int
__iomap_write_begin(struct inode *inode, loff_t pos, unsigned len,
		struct page *page, struct iomap *iomap)
{
	struct iomap_page *iop = iomap_page_create(inode, page);
	loff_t block_size = i_blocksize(inode);
	loff_t block_start = pos & ~(block_size - 1);
	loff_t block_end = (pos + len + block_size - 1) & ~(block_size - 1);
	unsigned from = offset_in_page(pos), to = from + len, poff, plen;
	int status = 0;

	if (PageUptodate(page))
		return 0;

	do {
		iomap_adjust_read_range(inode, iop, &block_start,
				block_end - block_start, &poff, &plen);
		if (plen == 0)
			break;

		if ((from > poff && from < poff + plen) ||
		    (to > poff && to < poff + plen)) {
			status = iomap_read_page_sync(inode, block_start, page,
					poff, plen, from, to, iomap);
			if (status)
				break;
		}

	} while ((block_start += plen) < block_end);

	return status;
}