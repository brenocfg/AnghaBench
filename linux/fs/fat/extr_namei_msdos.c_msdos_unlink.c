#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  S_CTIME ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 
 int fat_flush_inodes (struct super_block*,struct inode*,struct inode*) ; 
 int fat_remove_entries (struct inode*,struct fat_slot_info*) ; 
 int /*<<< orphan*/  fat_truncate_time (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int msdos_find (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fat_slot_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msdos_unlink(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	struct super_block *sb = inode->i_sb;
	struct fat_slot_info sinfo;
	int err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);
	err = msdos_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	if (err)
		goto out;

	err = fat_remove_entries(dir, &sinfo);	/* and releases bh */
	if (err)
		goto out;
	clear_nlink(inode);
	fat_truncate_time(inode, NULL, S_CTIME);
	fat_detach(inode);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	if (!err)
		err = fat_flush_inodes(sb, dir, inode);

	return err;
}