#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nilfs_shadow_map {int /*<<< orphan*/  frozen_buffers; int /*<<< orphan*/  frozen_data; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {int /*<<< orphan*/  b_assoc_buffers; TYPE_1__* b_page; } ;
struct TYPE_4__ {struct nilfs_shadow_map* mi_shadow; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int,int /*<<< orphan*/ ) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_copy_buffer (struct buffer_head*,struct buffer_head*) ; 
 struct buffer_head* nilfs_page_get_nth_block (struct page*,int) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_buffer_nilfs_redirected (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nilfs_mdt_freeze_buffer(struct inode *inode, struct buffer_head *bh)
{
	struct nilfs_shadow_map *shadow = NILFS_MDT(inode)->mi_shadow;
	struct buffer_head *bh_frozen;
	struct page *page;
	int blkbits = inode->i_blkbits;

	page = grab_cache_page(&shadow->frozen_data, bh->b_page->index);
	if (!page)
		return -ENOMEM;

	if (!page_has_buffers(page))
		create_empty_buffers(page, 1 << blkbits, 0);

	bh_frozen = nilfs_page_get_nth_block(page, bh_offset(bh) >> blkbits);

	if (!buffer_uptodate(bh_frozen))
		nilfs_copy_buffer(bh_frozen, bh);
	if (list_empty(&bh_frozen->b_assoc_buffers)) {
		list_add_tail(&bh_frozen->b_assoc_buffers,
			      &shadow->frozen_buffers);
		set_buffer_nilfs_redirected(bh);
	} else {
		brelse(bh_frozen); /* already frozen */
	}

	unlock_page(page);
	put_page(page);
	return 0;
}