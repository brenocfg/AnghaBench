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
struct buffer_head {unsigned long b_state; struct buffer_head* b_this_page; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Dirty ; 
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 unsigned long NILFS_BUFFER_INHERENT_BITS ; 
 scalar_t__ PageMappedToDisk (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void nilfs_copy_page(struct page *dst, struct page *src, int copy_dirty)
{
	struct buffer_head *dbh, *dbufs, *sbh, *sbufs;
	unsigned long mask = NILFS_BUFFER_INHERENT_BITS;

	BUG_ON(PageWriteback(dst));

	sbh = sbufs = page_buffers(src);
	if (!page_has_buffers(dst))
		create_empty_buffers(dst, sbh->b_size, 0);

	if (copy_dirty)
		mask |= BIT(BH_Dirty);

	dbh = dbufs = page_buffers(dst);
	do {
		lock_buffer(sbh);
		lock_buffer(dbh);
		dbh->b_state = sbh->b_state & mask;
		dbh->b_blocknr = sbh->b_blocknr;
		dbh->b_bdev = sbh->b_bdev;
		sbh = sbh->b_this_page;
		dbh = dbh->b_this_page;
	} while (dbh != dbufs);

	copy_highpage(dst, src);

	if (PageUptodate(src) && !PageUptodate(dst))
		SetPageUptodate(dst);
	else if (!PageUptodate(src) && PageUptodate(dst))
		ClearPageUptodate(dst);
	if (PageMappedToDisk(src) && !PageMappedToDisk(dst))
		SetPageMappedToDisk(dst);
	else if (!PageMappedToDisk(src) && PageMappedToDisk(dst))
		ClearPageMappedToDisk(dst);

	do {
		unlock_buffer(sbh);
		unlock_buffer(dbh);
		sbh = sbh->b_this_page;
		dbh = dbh->b_this_page;
	} while (dbh != dbufs);
}