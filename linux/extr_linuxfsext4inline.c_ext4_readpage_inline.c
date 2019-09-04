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
struct page {int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_read_inline_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ext4_readpage_inline(struct inode *inode, struct page *page)
{
	int ret = 0;

	down_read(&EXT4_I(inode)->xattr_sem);
	if (!ext4_has_inline_data(inode)) {
		up_read(&EXT4_I(inode)->xattr_sem);
		return -EAGAIN;
	}

	/*
	 * Current inline data can only exist in the 1st page,
	 * So for all the other pages, just set them uptodate.
	 */
	if (!page->index)
		ret = ext4_read_inline_page(inode, page);
	else if (!PageUptodate(page)) {
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
	}

	up_read(&EXT4_I(inode)->xattr_sem);

	unlock_page(page);
	return ret >= 0 ? 0 : ret;
}