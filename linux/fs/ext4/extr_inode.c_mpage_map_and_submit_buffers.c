#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pagevec {struct page** pages; } ;
struct page {int dummy; } ;
struct TYPE_6__ {int m_lblk; int m_len; scalar_t__ m_flags; int /*<<< orphan*/  m_pblk; } ;
struct TYPE_5__ {TYPE_1__* io_end; } ;
struct mpage_da_data {TYPE_3__ map; TYPE_2__ io_submit; struct inode* inode; } ;
struct inode {int i_blkbits; int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {scalar_t__ b_blocknr; struct buffer_head* b_this_page; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int pgoff_t ;
typedef  int ext4_lblk_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_unwritten (struct buffer_head*) ; 
 int mpage_process_page_bufs (struct mpage_da_data*,struct buffer_head*,struct buffer_head*,int) ; 
 int mpage_submit_page (struct mpage_da_data*,struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int pagevec_lookup_range (struct pagevec*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 

__attribute__((used)) static int mpage_map_and_submit_buffers(struct mpage_da_data *mpd)
{
	struct pagevec pvec;
	int nr_pages, i;
	struct inode *inode = mpd->inode;
	struct buffer_head *head, *bh;
	int bpp_bits = PAGE_SHIFT - inode->i_blkbits;
	pgoff_t start, end;
	ext4_lblk_t lblk;
	sector_t pblock;
	int err;

	start = mpd->map.m_lblk >> bpp_bits;
	end = (mpd->map.m_lblk + mpd->map.m_len - 1) >> bpp_bits;
	lblk = start << bpp_bits;
	pblock = mpd->map.m_pblk;

	pagevec_init(&pvec);
	while (start <= end) {
		nr_pages = pagevec_lookup_range(&pvec, inode->i_mapping,
						&start, end);
		if (nr_pages == 0)
			break;
		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];

			bh = head = page_buffers(page);
			do {
				if (lblk < mpd->map.m_lblk)
					continue;
				if (lblk >= mpd->map.m_lblk + mpd->map.m_len) {
					/*
					 * Buffer after end of mapped extent.
					 * Find next buffer in the page to map.
					 */
					mpd->map.m_len = 0;
					mpd->map.m_flags = 0;
					/*
					 * FIXME: If dioread_nolock supports
					 * blocksize < pagesize, we need to make
					 * sure we add size mapped so far to
					 * io_end->size as the following call
					 * can submit the page for IO.
					 */
					err = mpage_process_page_bufs(mpd, head,
								      bh, lblk);
					pagevec_release(&pvec);
					if (err > 0)
						err = 0;
					return err;
				}
				if (buffer_delay(bh)) {
					clear_buffer_delay(bh);
					bh->b_blocknr = pblock++;
				}
				clear_buffer_unwritten(bh);
			} while (lblk++, (bh = bh->b_this_page) != head);

			/*
			 * FIXME: This is going to break if dioread_nolock
			 * supports blocksize < pagesize as we will try to
			 * convert potentially unmapped parts of inode.
			 */
			mpd->io_submit.io_end->size += PAGE_SIZE;
			/* Page fully mapped - let IO run! */
			err = mpage_submit_page(mpd, page);
			if (err < 0) {
				pagevec_release(&pvec);
				return err;
			}
		}
		pagevec_release(&pvec);
	}
	/* Extent fully mapped and matches with page boundary. We are done. */
	mpd->map.m_len = 0;
	mpd->map.m_flags = 0;
	return 0;
}