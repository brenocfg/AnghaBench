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
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_lock; int /*<<< orphan*/  needs_free_space; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FREE_SPACE_TREE ; 
 int __add_block_group_free_space (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_fs_compat_ro (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int add_block_group_free_space(struct btrfs_trans_handle *trans,
			       struct btrfs_block_group_cache *block_group)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_path *path = NULL;
	int ret = 0;

	if (!btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE))
		return 0;

	mutex_lock(&block_group->free_space_lock);
	if (!block_group->needs_free_space)
		goto out;

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	ret = __add_block_group_free_space(trans, block_group, path);

out:
	btrfs_free_path(path);
	mutex_unlock(&block_group->free_space_lock);
	if (ret)
		btrfs_abort_transaction(trans, ret);
	return ret;
}