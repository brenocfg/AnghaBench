#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_path {int search_commit_root; int skip_locking; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; } ;
struct btrfs_free_space_ctl {scalar_t__ free_space; int /*<<< orphan*/  tree_lock; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {scalar_t__ disk_cache_state; scalar_t__ bytes_super; TYPE_1__ key; int /*<<< orphan*/  lock; int /*<<< orphan*/  item; struct btrfs_free_space_ctl* free_space_ctl; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 scalar_t__ BTRFS_DC_CLEAR ; 
 scalar_t__ BTRFS_DC_WRITTEN ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (struct btrfs_free_space_ctl*) ; 
 int __load_free_space_cache (int /*<<< orphan*/ ,struct inode*,struct btrfs_free_space_ctl*,struct btrfs_path*,int /*<<< orphan*/ ) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 scalar_t__ btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* lookup_free_space_inode (struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int load_free_space_cache(struct btrfs_block_group_cache *block_group)
{
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	struct inode *inode;
	struct btrfs_path *path;
	int ret = 0;
	bool matched;
	u64 used = btrfs_block_group_used(&block_group->item);

	/*
	 * If this block group has been marked to be cleared for one reason or
	 * another then we can't trust the on disk cache, so just return.
	 */
	spin_lock(&block_group->lock);
	if (block_group->disk_cache_state != BTRFS_DC_WRITTEN) {
		spin_unlock(&block_group->lock);
		return 0;
	}
	spin_unlock(&block_group->lock);

	path = btrfs_alloc_path();
	if (!path)
		return 0;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	/*
	 * We must pass a path with search_commit_root set to btrfs_iget in
	 * order to avoid a deadlock when allocating extents for the tree root.
	 *
	 * When we are COWing an extent buffer from the tree root, when looking
	 * for a free extent, at extent-tree.c:find_free_extent(), we can find
	 * block group without its free space cache loaded. When we find one
	 * we must load its space cache which requires reading its free space
	 * cache's inode item from the root tree. If this inode item is located
	 * in the same leaf that we started COWing before, then we end up in
	 * deadlock on the extent buffer (trying to read lock it when we
	 * previously write locked it).
	 *
	 * It's safe to read the inode item using the commit root because
	 * block groups, once loaded, stay in memory forever (until they are
	 * removed) as well as their space caches once loaded. New block groups
	 * once created get their ->cached field set to BTRFS_CACHE_FINISHED so
	 * we will never try to read their inode item while the fs is mounted.
	 */
	inode = lookup_free_space_inode(block_group, path);
	if (IS_ERR(inode)) {
		btrfs_free_path(path);
		return 0;
	}

	/* We may have converted the inode and made the cache invalid. */
	spin_lock(&block_group->lock);
	if (block_group->disk_cache_state != BTRFS_DC_WRITTEN) {
		spin_unlock(&block_group->lock);
		btrfs_free_path(path);
		goto out;
	}
	spin_unlock(&block_group->lock);

	ret = __load_free_space_cache(fs_info->tree_root, inode, ctl,
				      path, block_group->key.objectid);
	btrfs_free_path(path);
	if (ret <= 0)
		goto out;

	spin_lock(&ctl->tree_lock);
	matched = (ctl->free_space == (block_group->key.offset - used -
				       block_group->bytes_super));
	spin_unlock(&ctl->tree_lock);

	if (!matched) {
		__btrfs_remove_free_space_cache(ctl);
		btrfs_warn(fs_info,
			   "block group %llu has wrong amount of free space",
			   block_group->key.objectid);
		ret = -1;
	}
out:
	if (ret < 0) {
		/* This cache is bogus, make sure it gets cleared */
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
		spin_unlock(&block_group->lock);
		ret = 0;

		btrfs_warn(fs_info,
			   "failed to load free space cache for block group %llu, rebuilding it now",
			   block_group->key.objectid);
	}

	iput(inode);
	return ret;
}