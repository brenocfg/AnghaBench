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
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_state; struct page* b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Async_Write ; 
 int /*<<< orphan*/  BH_Dirty ; 
 int /*<<< orphan*/  BH_Mapped ; 
 int /*<<< orphan*/  BH_NILFS_Checked ; 
 int /*<<< orphan*/  BH_NILFS_Redirected ; 
 int /*<<< orphan*/  BH_NILFS_Volatile ; 
 int /*<<< orphan*/  BH_Uptodate ; 
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __nilfs_clear_page_dirty (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 scalar_t__ nilfs_page_buffers_clean (struct page*) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,unsigned long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void nilfs_forget_buffer(struct buffer_head *bh)
{
	struct page *page = bh->b_page;
	const unsigned long clear_bits =
		(BIT(BH_Uptodate) | BIT(BH_Dirty) | BIT(BH_Mapped) |
		 BIT(BH_Async_Write) | BIT(BH_NILFS_Volatile) |
		 BIT(BH_NILFS_Checked) | BIT(BH_NILFS_Redirected));

	lock_buffer(bh);
	set_mask_bits(&bh->b_state, clear_bits, 0);
	if (nilfs_page_buffers_clean(page))
		__nilfs_clear_page_dirty(page);

	bh->b_blocknr = -1;
	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);
	unlock_buffer(bh);
	brelse(bh);
}