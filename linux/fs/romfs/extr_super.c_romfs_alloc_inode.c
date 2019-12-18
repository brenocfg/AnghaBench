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
struct inode {int dummy; } ;
struct romfs_inode_info {struct inode vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct romfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  romfs_inode_cachep ; 

__attribute__((used)) static struct inode *romfs_alloc_inode(struct super_block *sb)
{
	struct romfs_inode_info *inode;

	inode = kmem_cache_alloc(romfs_inode_cachep, GFP_KERNEL);
	return inode ? &inode->vfs_inode : NULL;
}