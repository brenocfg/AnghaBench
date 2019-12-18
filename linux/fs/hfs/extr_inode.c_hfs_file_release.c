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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opencnt; struct inode* rsrc_inode; } ;

/* Variables and functions */
 TYPE_1__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_file_truncate (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int hfs_file_release(struct inode *inode, struct file *file)
{
	//struct super_block *sb = inode->i_sb;

	if (HFS_IS_RSRC(inode))
		inode = HFS_I(inode)->rsrc_inode;
	if (atomic_dec_and_test(&HFS_I(inode)->opencnt)) {
		inode_lock(inode);
		hfs_file_truncate(inode);
		//if (inode->i_flags & S_DEAD) {
		//	hfs_delete_cat(inode->i_ino, HFSPLUS_SB(sb).hidden_dir, NULL);
		//	hfs_delete_inode(inode);
		//}
		inode_unlock(inode);
	}
	return 0;
}