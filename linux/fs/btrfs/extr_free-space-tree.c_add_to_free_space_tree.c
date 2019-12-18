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
struct btrfs_trans_handle {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE_SPACE_TREE ; 
 int __add_to_free_space_tree (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_fs_compat_ro (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int add_to_free_space_tree(struct btrfs_trans_handle *trans,
			   u64 start, u64 size)
{
	struct btrfs_block_group_cache *block_group;
	struct btrfs_path *path;
	int ret;

	if (!btrfs_fs_compat_ro(trans->fs_info, FREE_SPACE_TREE))
		return 0;

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	block_group = btrfs_lookup_block_group(trans->fs_info, start);
	if (!block_group) {
		ASSERT(0);
		ret = -ENOENT;
		goto out;
	}

	mutex_lock(&block_group->free_space_lock);
	ret = __add_to_free_space_tree(trans, block_group, path, start, size);
	mutex_unlock(&block_group->free_space_lock);

	btrfs_put_block_group(block_group);
out:
	btrfs_free_path(path);
	if (ret)
		btrfs_abort_transaction(trans, ret);
	return ret;
}