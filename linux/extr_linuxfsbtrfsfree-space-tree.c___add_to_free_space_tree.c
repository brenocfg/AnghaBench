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
typedef  int u32 ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_info {int dummy; } ;
struct btrfs_block_group_cache {scalar_t__ needs_free_space; } ;

/* Variables and functions */
 int BTRFS_FREE_SPACE_USING_BITMAPS ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 int __add_block_group_free_space (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int add_free_space_extent (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_free_space_flags (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int modify_free_space_bitmap (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_free_space_info* search_free_space_info (int /*<<< orphan*/ *,struct btrfs_fs_info*,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ) ; 

int __add_to_free_space_tree(struct btrfs_trans_handle *trans,
			     struct btrfs_block_group_cache *block_group,
			     struct btrfs_path *path, u64 start, u64 size)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_free_space_info *info;
	u32 flags;
	int ret;

	if (block_group->needs_free_space) {
		ret = __add_block_group_free_space(trans, block_group, path);
		if (ret)
			return ret;
	}

	info = search_free_space_info(NULL, fs_info, block_group, path, 0);
	if (IS_ERR(info))
		return PTR_ERR(info);
	flags = btrfs_free_space_flags(path->nodes[0], info);
	btrfs_release_path(path);

	if (flags & BTRFS_FREE_SPACE_USING_BITMAPS) {
		return modify_free_space_bitmap(trans, block_group, path,
						start, size, 0);
	} else {
		return add_free_space_extent(trans, block_group, path, start,
					     size);
	}
}