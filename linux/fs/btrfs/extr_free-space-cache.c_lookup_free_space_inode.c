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
typedef  int u32 ;
struct inode {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {int iref; int /*<<< orphan*/  lock; struct inode* inode; int /*<<< orphan*/  disk_cache_state; TYPE_1__ key; struct btrfs_fs_info* fs_info; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DC_CLEAR ; 
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATACOW ; 
 int BTRFS_INODE_NODATASUM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* __lookup_free_space_inode (int /*<<< orphan*/ ,struct btrfs_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*) ; 
 void* igrab (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct inode *lookup_free_space_inode(
		struct btrfs_block_group_cache *block_group,
		struct btrfs_path *path)
{
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct inode *inode = NULL;
	u32 flags = BTRFS_INODE_NODATASUM | BTRFS_INODE_NODATACOW;

	spin_lock(&block_group->lock);
	if (block_group->inode)
		inode = igrab(block_group->inode);
	spin_unlock(&block_group->lock);
	if (inode)
		return inode;

	inode = __lookup_free_space_inode(fs_info->tree_root, path,
					  block_group->key.objectid);
	if (IS_ERR(inode))
		return inode;

	spin_lock(&block_group->lock);
	if (!((BTRFS_I(inode)->flags & flags) == flags)) {
		btrfs_info(fs_info, "Old style space inode found, converting.");
		BTRFS_I(inode)->flags |= BTRFS_INODE_NODATASUM |
			BTRFS_INODE_NODATACOW;
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
	}

	if (!block_group->iref) {
		block_group->inode = igrab(inode);
		block_group->iref = 1;
	}
	spin_unlock(&block_group->lock);

	return inode;
}