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
struct free_space_extent {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_info {int dummy; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int BTRFS_FREE_SPACE_USING_BITMAPS ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 int __check_free_space_extents (struct btrfs_trans_handle*,struct btrfs_fs_info*,struct btrfs_block_group_cache*,struct btrfs_path*,struct free_space_extent const* const,unsigned int) ; 
 int btrfs_free_space_flags (int /*<<< orphan*/ ,struct btrfs_free_space_info*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int convert_free_space_to_bitmaps (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int convert_free_space_to_extents (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 struct btrfs_free_space_info* search_free_space_info (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_err (char*) ; 

__attribute__((used)) static int check_free_space_extents(struct btrfs_trans_handle *trans,
				    struct btrfs_fs_info *fs_info,
				    struct btrfs_block_group_cache *cache,
				    struct btrfs_path *path,
				    const struct free_space_extent * const extents,
				    unsigned int num_extents)
{
	struct btrfs_free_space_info *info;
	u32 flags;
	int ret;

	info = search_free_space_info(trans, cache, path, 0);
	if (IS_ERR(info)) {
		test_err("could not find free space info");
		btrfs_release_path(path);
		return PTR_ERR(info);
	}
	flags = btrfs_free_space_flags(path->nodes[0], info);
	btrfs_release_path(path);

	ret = __check_free_space_extents(trans, fs_info, cache, path, extents,
					 num_extents);
	if (ret)
		return ret;

	/* Flip it to the other format and check that for good measure. */
	if (flags & BTRFS_FREE_SPACE_USING_BITMAPS) {
		ret = convert_free_space_to_extents(trans, cache, path);
		if (ret) {
			test_err("could not convert to extents");
			return ret;
		}
	} else {
		ret = convert_free_space_to_bitmaps(trans, cache, path);
		if (ret) {
			test_err("could not convert to bitmaps");
			return ret;
		}
	}
	return __check_free_space_extents(trans, fs_info, cache, path, extents,
					  num_extents);
}