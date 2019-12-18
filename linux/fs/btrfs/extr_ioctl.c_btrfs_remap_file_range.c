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
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int REMAP_FILE_ADVISORY ; 
 unsigned int REMAP_FILE_DEDUP ; 
 int btrfs_clone_files (struct file*,struct file*,int,int,int) ; 
 int btrfs_extent_same (struct inode*,int,int,struct inode*,int) ; 
 int btrfs_remap_file_range_prep (struct file*,int,struct file*,int,int*,unsigned int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  lock_two_nondirectories (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  unlock_two_nondirectories (struct inode*,struct inode*) ; 

loff_t btrfs_remap_file_range(struct file *src_file, loff_t off,
		struct file *dst_file, loff_t destoff, loff_t len,
		unsigned int remap_flags)
{
	struct inode *src_inode = file_inode(src_file);
	struct inode *dst_inode = file_inode(dst_file);
	bool same_inode = dst_inode == src_inode;
	int ret;

	if (remap_flags & ~(REMAP_FILE_DEDUP | REMAP_FILE_ADVISORY))
		return -EINVAL;

	if (same_inode)
		inode_lock(src_inode);
	else
		lock_two_nondirectories(src_inode, dst_inode);

	ret = btrfs_remap_file_range_prep(src_file, off, dst_file, destoff,
					  &len, remap_flags);
	if (ret < 0 || len == 0)
		goto out_unlock;

	if (remap_flags & REMAP_FILE_DEDUP)
		ret = btrfs_extent_same(src_inode, off, len, dst_inode, destoff);
	else
		ret = btrfs_clone_files(dst_file, src_file, off, len, destoff);

out_unlock:
	if (same_inode)
		inode_unlock(src_inode);
	else
		unlock_two_nondirectories(src_inode, dst_inode);

	return ret < 0 ? ret : len;
}