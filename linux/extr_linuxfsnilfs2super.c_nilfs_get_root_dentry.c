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
struct super_block {int dummy; } ;
struct nilfs_root {scalar_t__ cno; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ NILFS_CPTREE_CURRENT_CNO ; 
 int /*<<< orphan*/  NILFS_ROOT_INO ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct inode* d_find_alias (struct inode*) ; 
 struct inode* d_make_root (struct inode*) ; 
 struct inode* d_obtain_root (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* nilfs_iget (struct super_block*,struct nilfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int nilfs_get_root_dentry(struct super_block *sb,
				 struct nilfs_root *root,
				 struct dentry **root_dentry)
{
	struct inode *inode;
	struct dentry *dentry;
	int ret = 0;

	inode = nilfs_iget(sb, root, NILFS_ROOT_INO);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		nilfs_msg(sb, KERN_ERR, "error %d getting root inode", ret);
		goto out;
	}
	if (!S_ISDIR(inode->i_mode) || !inode->i_blocks || !inode->i_size) {
		iput(inode);
		nilfs_msg(sb, KERN_ERR, "corrupt root inode");
		ret = -EINVAL;
		goto out;
	}

	if (root->cno == NILFS_CPTREE_CURRENT_CNO) {
		dentry = d_find_alias(inode);
		if (!dentry) {
			dentry = d_make_root(inode);
			if (!dentry) {
				ret = -ENOMEM;
				goto failed_dentry;
			}
		} else {
			iput(inode);
		}
	} else {
		dentry = d_obtain_root(inode);
		if (IS_ERR(dentry)) {
			ret = PTR_ERR(dentry);
			goto failed_dentry;
		}
	}
	*root_dentry = dentry;
 out:
	return ret;

 failed_dentry:
	nilfs_msg(sb, KERN_ERR, "error %d getting root dentry", ret);
	goto out;
}