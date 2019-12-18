#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_4__ {scalar_t__ objectid; } ;
struct btrfs_inode {TYPE_2__ location; struct btrfs_root* root; } ;
struct TYPE_3__ {struct btrfs_root* tree_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_BTREE_INODE_OBJECTID ; 
 scalar_t__ BTRFS_FREE_INO_OBJECTID ; 
 scalar_t__ btrfs_ino (struct btrfs_inode*) ; 

__attribute__((used)) static inline bool btrfs_is_free_space_inode(struct btrfs_inode *inode)
{
	struct btrfs_root *root = inode->root;

	if (root == root->fs_info->tree_root &&
	    btrfs_ino(inode) != BTRFS_BTREE_INODE_OBJECTID)
		return true;
	if (inode->location.objectid == BTRFS_FREE_INO_OBJECTID)
		return true;
	return false;
}