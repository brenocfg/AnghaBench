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
struct page {scalar_t__ index; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  f2fs_do_read_inline_data (struct page*,struct page*) ; 
 struct page* f2fs_get_node_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int f2fs_read_inline_data(struct inode *inode, struct page *page)
{
	struct page *ipage;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	if (IS_ERR(ipage)) {
		unlock_page(page);
		return PTR_ERR(ipage);
	}

	if (!f2fs_has_inline_data(inode)) {
		f2fs_put_page(ipage, 1);
		return -EAGAIN;
	}

	if (page->index)
		zero_user_segment(page, 0, PAGE_SIZE);
	else
		f2fs_do_read_inline_data(page, ipage);

	if (!PageUptodate(page))
		SetPageUptodate(page);
	f2fs_put_page(ipage, 1);
	unlock_page(page);
	return 0;
}