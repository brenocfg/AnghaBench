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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_tmpfile (struct dentry*,struct inode*) ; 
 struct inode* ext2_new_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2_set_file_ops (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext2_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode = ext2_new_inode(dir, mode, NULL);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	ext2_set_file_ops(inode);
	mark_inode_dirty(inode);
	d_tmpfile(dentry, inode);
	unlock_new_inode(inode);
	return 0;
}