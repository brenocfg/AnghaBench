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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct nilfs_root {int dummy; } ;
struct inode {scalar_t__ i_generation; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  NILFS_FIRST_INO (struct super_block*) ; 
 int /*<<< orphan*/  NILFS_ROOT_INO ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* nilfs_iget (struct super_block*,struct nilfs_root*,int /*<<< orphan*/ ) ; 
 struct nilfs_root* nilfs_lookup_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_put_root (struct nilfs_root*) ; 

__attribute__((used)) static struct dentry *nilfs_get_dentry(struct super_block *sb, u64 cno,
				       u64 ino, u32 gen)
{
	struct nilfs_root *root;
	struct inode *inode;

	if (ino < NILFS_FIRST_INO(sb) && ino != NILFS_ROOT_INO)
		return ERR_PTR(-ESTALE);

	root = nilfs_lookup_root(sb->s_fs_info, cno);
	if (!root)
		return ERR_PTR(-ESTALE);

	inode = nilfs_iget(sb, root, ino);
	nilfs_put_root(root);

	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (gen && inode->i_generation != gen) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}
	return d_obtain_alias(inode);
}