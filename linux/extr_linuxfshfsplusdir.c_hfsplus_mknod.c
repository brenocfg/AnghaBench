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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct hfsplus_sb_info {int /*<<< orphan*/  vh_mutex; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int hfsplus_create_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  hfsplus_delete_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int hfsplus_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_instantiate (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* hfsplus_new_inode (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfsplus_mknod(struct inode *dir, struct dentry *dentry,
			 umode_t mode, dev_t rdev)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	struct inode *inode;
	int res = -ENOMEM;

	mutex_lock(&sbi->vh_mutex);
	inode = hfsplus_new_inode(dir->i_sb, dir, mode);
	if (!inode)
		goto out;

	if (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISSOCK(mode))
		init_special_inode(inode, mode, rdev);

	res = hfsplus_create_cat(inode->i_ino, dir, &dentry->d_name, inode);
	if (res)
		goto failed_mknod;

	res = hfsplus_init_security(inode, dir, &dentry->d_name);
	if (res == -EOPNOTSUPP)
		res = 0; /* Operation is not supported. */
	else if (res) {
		/* Try to delete anyway without error analysis. */
		hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
		goto failed_mknod;
	}

	hfsplus_instantiate(dentry, inode, inode->i_ino);
	mark_inode_dirty(inode);
	goto out;

failed_mknod:
	clear_nlink(inode);
	hfsplus_delete_inode(inode);
	iput(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}