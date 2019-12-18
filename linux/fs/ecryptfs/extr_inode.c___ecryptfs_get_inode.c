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
struct inode {scalar_t__ i_sb; int i_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  EXDEV ; 
 int I_NEW ; 
 int /*<<< orphan*/  ecryptfs_inode_set ; 
 int /*<<< orphan*/  ecryptfs_inode_test ; 
 scalar_t__ ecryptfs_superblock_to_lower (struct super_block*) ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct inode *__ecryptfs_get_inode(struct inode *lower_inode,
					  struct super_block *sb)
{
	struct inode *inode;

	if (lower_inode->i_sb != ecryptfs_superblock_to_lower(sb))
		return ERR_PTR(-EXDEV);
	if (!igrab(lower_inode))
		return ERR_PTR(-ESTALE);
	inode = iget5_locked(sb, (unsigned long)lower_inode,
			     ecryptfs_inode_test, ecryptfs_inode_set,
			     lower_inode);
	if (!inode) {
		iput(lower_inode);
		return ERR_PTR(-EACCES);
	}
	if (!(inode->i_state & I_NEW))
		iput(lower_inode);

	return inode;
}