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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sem; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_add_orphan_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_links_write (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_release_orphan_inode (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void f2fs_drop_nlink(struct inode *dir, struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);

	down_write(&F2FS_I(inode)->i_sem);

	if (S_ISDIR(inode->i_mode))
		f2fs_i_links_write(dir, false);
	inode->i_ctime = current_time(inode);

	f2fs_i_links_write(inode, false);
	if (S_ISDIR(inode->i_mode)) {
		f2fs_i_links_write(inode, false);
		f2fs_i_size_write(inode, 0);
	}
	up_write(&F2FS_I(inode)->i_sem);

	if (inode->i_nlink == 0)
		f2fs_add_orphan_inode(inode);
	else
		f2fs_release_orphan_inode(sbi);
}