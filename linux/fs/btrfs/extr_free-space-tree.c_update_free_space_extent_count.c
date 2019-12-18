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
typedef  scalar_t__ u32 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_free_space_info {int dummy; } ;
struct btrfs_block_group_cache {scalar_t__ bitmap_high_thresh; scalar_t__ bitmap_low_thresh; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FREE_SPACE_USING_BITMAPS ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 scalar_t__ btrfs_free_space_extent_count (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 scalar_t__ btrfs_free_space_flags (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_set_free_space_extent_count (int /*<<< orphan*/ ,struct btrfs_free_space_info*,scalar_t__) ; 
 int convert_free_space_to_bitmaps (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int convert_free_space_to_extents (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 struct btrfs_free_space_info* search_free_space_info (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*,int) ; 

__attribute__((used)) static int update_free_space_extent_count(struct btrfs_trans_handle *trans,
					  struct btrfs_block_group_cache *block_group,
					  struct btrfs_path *path,
					  int new_extents)
{
	struct btrfs_free_space_info *info;
	u32 flags;
	u32 extent_count;
	int ret = 0;

	if (new_extents == 0)
		return 0;

	info = search_free_space_info(trans, block_group, path, 1);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto out;
	}
	flags = btrfs_free_space_flags(path->nodes[0], info);
	extent_count = btrfs_free_space_extent_count(path->nodes[0], info);

	extent_count += new_extents;
	btrfs_set_free_space_extent_count(path->nodes[0], info, extent_count);
	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_release_path(path);

	if (!(flags & BTRFS_FREE_SPACE_USING_BITMAPS) &&
	    extent_count > block_group->bitmap_high_thresh) {
		ret = convert_free_space_to_bitmaps(trans, block_group, path);
	} else if ((flags & BTRFS_FREE_SPACE_USING_BITMAPS) &&
		   extent_count < block_group->bitmap_low_thresh) {
		ret = convert_free_space_to_extents(trans, block_group, path);
	}

out:
	return ret;
}