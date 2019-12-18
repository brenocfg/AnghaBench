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
typedef  int u32 ;
struct btrfs_path {int skip_locking; int search_commit_root; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  reada; } ;
struct btrfs_free_space_info {int dummy; } ;
struct btrfs_caching_control {struct btrfs_block_group_cache* block_group; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int BTRFS_FREE_SPACE_USING_BITMAPS ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 int /*<<< orphan*/  READA_FORWARD ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_free_space_extent_count (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 int btrfs_free_space_flags (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 int load_free_space_bitmaps (struct btrfs_caching_control*,struct btrfs_path*,int) ; 
 int load_free_space_extents (struct btrfs_caching_control*,struct btrfs_path*,int) ; 
 struct btrfs_free_space_info* search_free_space_info (int /*<<< orphan*/ *,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ) ; 

int load_free_space_tree(struct btrfs_caching_control *caching_ctl)
{
	struct btrfs_block_group_cache *block_group;
	struct btrfs_free_space_info *info;
	struct btrfs_path *path;
	u32 extent_count, flags;
	int ret;

	block_group = caching_ctl->block_group;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	/*
	 * Just like caching_thread() doesn't want to deadlock on the extent
	 * tree, we don't want to deadlock on the free space tree.
	 */
	path->skip_locking = 1;
	path->search_commit_root = 1;
	path->reada = READA_FORWARD;

	info = search_free_space_info(NULL, block_group, path, 0);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto out;
	}
	extent_count = btrfs_free_space_extent_count(path->nodes[0], info);
	flags = btrfs_free_space_flags(path->nodes[0], info);

	/*
	 * We left path pointing to the free space info item, so now
	 * load_free_space_foo can just iterate through the free space tree from
	 * there.
	 */
	if (flags & BTRFS_FREE_SPACE_USING_BITMAPS)
		ret = load_free_space_bitmaps(caching_ctl, path, extent_count);
	else
		ret = load_free_space_extents(caching_ctl, path, extent_count);

out:
	btrfs_free_path(path);
	return ret;
}