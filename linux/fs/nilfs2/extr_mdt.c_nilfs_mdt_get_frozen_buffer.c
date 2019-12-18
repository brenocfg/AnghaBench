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
struct nilfs_shadow_map {int /*<<< orphan*/  frozen_data; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {TYPE_1__* b_page; } ;
struct TYPE_4__ {struct nilfs_shadow_map* mi_shadow; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 struct page* find_lock_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct buffer_head* nilfs_page_get_nth_block (struct page*,int) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct buffer_head *
nilfs_mdt_get_frozen_buffer(struct inode *inode, struct buffer_head *bh)
{
	struct nilfs_shadow_map *shadow = NILFS_MDT(inode)->mi_shadow;
	struct buffer_head *bh_frozen = NULL;
	struct page *page;
	int n;

	page = find_lock_page(&shadow->frozen_data, bh->b_page->index);
	if (page) {
		if (page_has_buffers(page)) {
			n = bh_offset(bh) >> inode->i_blkbits;
			bh_frozen = nilfs_page_get_nth_block(page, n);
		}
		unlock_page(page);
		put_page(page);
	}
	return bh_frozen;
}