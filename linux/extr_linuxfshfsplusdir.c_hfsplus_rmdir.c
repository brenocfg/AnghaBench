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
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  vh_mutex; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int hfsplus_delete_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfsplus_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	struct inode *inode = d_inode(dentry);
	int res;

	if (inode->i_size != 2)
		return -ENOTEMPTY;

	mutex_lock(&sbi->vh_mutex);
	res = hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
	if (res)
		goto out;
	clear_nlink(inode);
	inode->i_ctime = current_time(inode);
	hfsplus_delete_inode(inode);
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}