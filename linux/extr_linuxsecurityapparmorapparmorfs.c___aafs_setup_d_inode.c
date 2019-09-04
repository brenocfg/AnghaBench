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
struct inode_operations {int dummy; } ;
struct inode {char* i_link; struct file_operations const* i_fop; struct inode_operations const* i_op; void* i_private; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int ENOMEM ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 struct inode_operations const simple_dir_inode_operations ; 
 struct file_operations const simple_dir_operations ; 
 struct inode_operations const simple_symlink_inode_operations ; 

__attribute__((used)) static int __aafs_setup_d_inode(struct inode *dir, struct dentry *dentry,
			       umode_t mode, void *data, char *link,
			       const struct file_operations *fops,
			       const struct inode_operations *iops)
{
	struct inode *inode = new_inode(dir->i_sb);

	AA_BUG(!dir);
	AA_BUG(!dentry);

	if (!inode)
		return -ENOMEM;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	inode->i_private = data;
	if (S_ISDIR(mode)) {
		inode->i_op = iops ? iops : &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(inode);
		inc_nlink(dir);
	} else if (S_ISLNK(mode)) {
		inode->i_op = iops ? iops : &simple_symlink_inode_operations;
		inode->i_link = link;
	} else {
		inode->i_fop = fops;
	}
	d_instantiate(dentry, inode);
	dget(dentry);

	return 0;
}