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
struct super_block {int dummy; } ;
struct kernfs_super_info {int /*<<< orphan*/  root; } ;
struct kernfs_node {int dummy; } ;
struct inode {scalar_t__ i_generation; } ;

/* Variables and functions */
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct kernfs_node* kernfs_find_and_get_node_by_ino (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* kernfs_get_inode (struct super_block*,struct kernfs_node*) ; 
 struct kernfs_super_info* kernfs_info (struct super_block*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 

__attribute__((used)) static struct inode *kernfs_fh_get_inode(struct super_block *sb,
		u64 ino, u32 generation)
{
	struct kernfs_super_info *info = kernfs_info(sb);
	struct inode *inode;
	struct kernfs_node *kn;

	if (ino == 0)
		return ERR_PTR(-ESTALE);

	kn = kernfs_find_and_get_node_by_ino(info->root, ino);
	if (!kn)
		return ERR_PTR(-ESTALE);
	inode = kernfs_get_inode(sb, kn);
	kernfs_put(kn);
	if (!inode)
		return ERR_PTR(-ESTALE);

	if (generation && inode->i_generation != generation) {
		/* we didn't find the right inode.. */
		iput(inode);
		return ERR_PTR(-ESTALE);
	}
	return inode;
}