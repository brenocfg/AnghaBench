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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int S_ATIME ; 
 int S_MTIME ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 
 int fat_remove_entries (struct inode*,struct fat_slot_info*) ; 
 int /*<<< orphan*/  fat_truncate_time (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfat_d_version_set (struct dentry*,int /*<<< orphan*/ ) ; 
 int vfat_find (struct inode*,int /*<<< orphan*/ *,struct fat_slot_info*) ; 

__attribute__((used)) static int vfat_unlink(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	struct super_block *sb = dir->i_sb;
	struct fat_slot_info sinfo;
	int err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = vfat_find(dir, &dentry->d_name, &sinfo);
	if (err)
		goto out;

	err = fat_remove_entries(dir, &sinfo);	/* and releases bh */
	if (err)
		goto out;
	clear_nlink(inode);
	fat_truncate_time(inode, NULL, S_ATIME|S_MTIME);
	fat_detach(inode);
	vfat_d_version_set(dentry, inode_query_iversion(dir));
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);

	return err;
}