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
struct inode {int dummy; } ;
struct vxfs_inode_info {struct inode vfs_inode; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  inode_init_once (struct inode*) ; 
 struct vxfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxfs_inode_cachep ; 

__attribute__((used)) static struct inode *vxfs_alloc_inode(struct super_block *sb)
{
	struct vxfs_inode_info *vi;

	vi = kmem_cache_alloc(vxfs_inode_cachep, GFP_KERNEL);
	if (!vi)
		return NULL;
	inode_init_once(&vi->vfs_inode);
	return &vi->vfs_inode;
}