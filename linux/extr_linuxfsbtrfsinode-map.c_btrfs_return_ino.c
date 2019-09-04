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
struct btrfs_root {scalar_t__ ino_cache_state; int /*<<< orphan*/  ino_cache_lock; struct btrfs_free_space_ctl* free_ino_pinned; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  commit_root_sem; } ;
struct btrfs_free_space_ctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int /*<<< orphan*/  __btrfs_add_free_space (struct btrfs_fs_info*,struct btrfs_free_space_ctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_caching (struct btrfs_root*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void btrfs_return_ino(struct btrfs_root *root, u64 objectid)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_free_space_ctl *pinned = root->free_ino_pinned;

	if (!btrfs_test_opt(fs_info, INODE_MAP_CACHE))
		return;
again:
	if (root->ino_cache_state == BTRFS_CACHE_FINISHED) {
		__btrfs_add_free_space(fs_info, pinned, objectid, 1);
	} else {
		down_write(&fs_info->commit_root_sem);
		spin_lock(&root->ino_cache_lock);
		if (root->ino_cache_state == BTRFS_CACHE_FINISHED) {
			spin_unlock(&root->ino_cache_lock);
			up_write(&fs_info->commit_root_sem);
			goto again;
		}
		spin_unlock(&root->ino_cache_lock);

		start_caching(root);

		__btrfs_add_free_space(fs_info, pinned, objectid, 1);

		up_write(&fs_info->commit_root_sem);
	}
}