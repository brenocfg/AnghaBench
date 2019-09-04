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
struct inode {int i_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int I_NEW ; 
 struct inode* __ecryptfs_get_inode (struct inode*,struct super_block*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ecryptfs_get_inode(struct inode *lower_inode,
				 struct super_block *sb)
{
	struct inode *inode = __ecryptfs_get_inode(lower_inode, sb);

	if (!IS_ERR(inode) && (inode->i_state & I_NEW))
		unlock_new_inode(inode);

	return inode;
}