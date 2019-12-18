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
struct pagevec {scalar_t__ nr; struct page** pages; } ;
struct page {int index; } ;
struct inode {unsigned int i_blkbits; TYPE_1__* i_mapping; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
typedef  unsigned int sector_t ;
typedef  int pgoff_t ;
struct TYPE_2__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ find_get_pages_contig (TYPE_1__*,int,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

unsigned long nilfs_find_uncommitted_extent(struct inode *inode,
					    sector_t start_blk,
					    sector_t *blkoff)
{
	unsigned int i;
	pgoff_t index;
	unsigned int nblocks_in_page;
	unsigned long length = 0;
	sector_t b;
	struct pagevec pvec;
	struct page *page;

	if (inode->i_mapping->nrpages == 0)
		return 0;

	index = start_blk >> (PAGE_SHIFT - inode->i_blkbits);
	nblocks_in_page = 1U << (PAGE_SHIFT - inode->i_blkbits);

	pagevec_init(&pvec);

repeat:
	pvec.nr = find_get_pages_contig(inode->i_mapping, index, PAGEVEC_SIZE,
					pvec.pages);
	if (pvec.nr == 0)
		return length;

	if (length > 0 && pvec.pages[0]->index > index)
		goto out;

	b = pvec.pages[0]->index << (PAGE_SHIFT - inode->i_blkbits);
	i = 0;
	do {
		page = pvec.pages[i];

		lock_page(page);
		if (page_has_buffers(page)) {
			struct buffer_head *bh, *head;

			bh = head = page_buffers(page);
			do {
				if (b < start_blk)
					continue;
				if (buffer_delay(bh)) {
					if (length == 0)
						*blkoff = b;
					length++;
				} else if (length > 0) {
					goto out_locked;
				}
			} while (++b, bh = bh->b_this_page, bh != head);
		} else {
			if (length > 0)
				goto out_locked;

			b += nblocks_in_page;
		}
		unlock_page(page);

	} while (++i < pagevec_count(&pvec));

	index = page->index + 1;
	pagevec_release(&pvec);
	cond_resched();
	goto repeat;

out_locked:
	unlock_page(page);
out:
	pagevec_release(&pvec);
	return length;
}