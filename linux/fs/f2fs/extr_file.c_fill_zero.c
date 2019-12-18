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
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 struct page* f2fs_get_new_data_page (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_zero(struct inode *inode, pgoff_t index,
					loff_t start, loff_t len)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct page *page;

	if (!len)
		return 0;

	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);
	page = f2fs_get_new_data_page(inode, NULL, index, false);
	f2fs_unlock_op(sbi);

	if (IS_ERR(page))
		return PTR_ERR(page);

	f2fs_wait_on_page_writeback(page, DATA, true, true);
	zero_user(page, start, len);
	set_page_dirty(page);
	f2fs_put_page(page, 1);
	return 0;
}