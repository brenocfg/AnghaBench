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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sem; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NEW_INODE ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct page* f2fs_init_inode_metadata (struct inode*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_update_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_do_tmpfile(struct inode *inode, struct inode *dir)
{
	struct page *page;
	int err = 0;

	down_write(&F2FS_I(inode)->i_sem);
	page = f2fs_init_inode_metadata(inode, dir, NULL, NULL, NULL);
	if (IS_ERR(page)) {
		err = PTR_ERR(page);
		goto fail;
	}
	f2fs_put_page(page, 1);

	clear_inode_flag(inode, FI_NEW_INODE);
	f2fs_update_time(F2FS_I_SB(inode), REQ_TIME);
fail:
	up_write(&F2FS_I(inode)->i_sem);
	return err;
}