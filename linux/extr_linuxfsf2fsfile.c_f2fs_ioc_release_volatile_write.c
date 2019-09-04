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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 int /*<<< orphan*/  f2fs_is_first_block_written (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_volatile_file (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int punch_hole (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int truncate_partial_data_page (struct inode*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int f2fs_ioc_release_volatile_write(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	int ret;

	if (!inode_owner_or_capable(inode))
		return -EACCES;

	ret = mnt_want_write_file(filp);
	if (ret)
		return ret;

	inode_lock(inode);

	if (!f2fs_is_volatile_file(inode))
		goto out;

	if (!f2fs_is_first_block_written(inode)) {
		ret = truncate_partial_data_page(inode, 0, true);
		goto out;
	}

	ret = punch_hole(inode, 0, F2FS_BLKSIZE);
out:
	inode_unlock(inode);
	mnt_drop_write_file(filp);
	return ret;
}