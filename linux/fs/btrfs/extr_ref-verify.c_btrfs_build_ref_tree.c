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
struct extent_buffer {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * locks; scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_fs_info {int /*<<< orphan*/  mount_opt; int /*<<< orphan*/  extent_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_READ_LOCK_BLOCKING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  REF_VERIFY ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_clear_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_free_ref_cache (struct btrfs_fs_info*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 struct extent_buffer* btrfs_read_lock_root_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_read (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int walk_down_tree (int /*<<< orphan*/ ,struct btrfs_path*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int walk_up_tree (struct btrfs_path*,int*) ; 

int btrfs_build_ref_tree(struct btrfs_fs_info *fs_info)
{
	struct btrfs_path *path;
	struct extent_buffer *eb;
	u64 bytenr = 0, num_bytes = 0;
	int ret, level;

	if (!btrfs_test_opt(fs_info, REF_VERIFY))
		return 0;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	eb = btrfs_read_lock_root_node(fs_info->extent_root);
	btrfs_set_lock_blocking_read(eb);
	level = btrfs_header_level(eb);
	path->nodes[level] = eb;
	path->slots[level] = 0;
	path->locks[level] = BTRFS_READ_LOCK_BLOCKING;

	while (1) {
		/*
		 * We have to keep track of the bytenr/num_bytes we last hit
		 * because we could have run out of space for an inline ref, and
		 * would have had to added a ref key item which may appear on a
		 * different leaf from the original extent item.
		 */
		ret = walk_down_tree(fs_info->extent_root, path, level,
				     &bytenr, &num_bytes);
		if (ret)
			break;
		ret = walk_up_tree(path, &level);
		if (ret < 0)
			break;
		if (ret > 0) {
			ret = 0;
			break;
		}
	}
	if (ret) {
		btrfs_clear_opt(fs_info->mount_opt, REF_VERIFY);
		btrfs_free_ref_cache(fs_info);
	}
	btrfs_free_path(path);
	return ret;
}