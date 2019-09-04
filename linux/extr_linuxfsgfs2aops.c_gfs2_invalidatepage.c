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
struct gfs2_sbd {int dummy; } ;
struct buffer_head {unsigned long b_size; struct buffer_head* b_this_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  gfs2_discard (struct gfs2_sbd*,struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_invalidatepage(struct page *page, unsigned int offset,
				unsigned int length)
{
	struct gfs2_sbd *sdp = GFS2_SB(page->mapping->host);
	unsigned int stop = offset + length;
	int partial_page = (offset || length < PAGE_SIZE);
	struct buffer_head *bh, *head;
	unsigned long pos = 0;

	BUG_ON(!PageLocked(page));
	if (!partial_page)
		ClearPageChecked(page);
	if (!page_has_buffers(page))
		goto out;

	bh = head = page_buffers(page);
	do {
		if (pos + bh->b_size > stop)
			return;

		if (offset <= pos)
			gfs2_discard(sdp, bh);
		pos += bh->b_size;
		bh = bh->b_this_page;
	} while (bh != head);
out:
	if (!partial_page)
		try_to_release_page(page, 0);
}