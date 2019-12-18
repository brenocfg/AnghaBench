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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_VOLATILE_FILE ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 scalar_t__ f2fs_is_volatile_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_update_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_inc_volatile_write (struct inode*) ; 
 int /*<<< orphan*/  stat_update_max_volatile_write (struct inode*) ; 

__attribute__((used)) static int f2fs_ioc_start_volatile_write(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	int ret;

	if (!inode_owner_or_capable(inode))
		return -EACCES;

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	ret = mnt_want_write_file(filp);
	if (ret)
		return ret;

	inode_lock(inode);

	if (f2fs_is_volatile_file(inode))
		goto out;

	ret = f2fs_convert_inline_inode(inode);
	if (ret)
		goto out;

	stat_inc_volatile_write(inode);
	stat_update_max_volatile_write(inode);

	set_inode_flag(inode, FI_VOLATILE_FILE);
	f2fs_update_time(F2FS_I_SB(inode), REQ_TIME);
out:
	inode_unlock(inode);
	mnt_drop_write_file(filp);
	return ret;
}