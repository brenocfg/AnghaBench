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
struct nilfs_root {int dummy; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 int __nilfs_read_inode (struct super_block*,struct nilfs_root*,unsigned long,struct inode*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* nilfs_iget_locked (struct super_block*,struct nilfs_root*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *nilfs_iget(struct super_block *sb, struct nilfs_root *root,
			 unsigned long ino)
{
	struct inode *inode;
	int err;

	inode = nilfs_iget_locked(sb, root, ino);
	if (unlikely(!inode))
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	err = __nilfs_read_inode(sb, root, ino, inode);
	if (unlikely(err)) {
		iget_failed(inode);
		return ERR_PTR(err);
	}
	unlock_new_inode(inode);
	return inode;
}