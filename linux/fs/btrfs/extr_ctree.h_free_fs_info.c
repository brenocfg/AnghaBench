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
struct btrfs_fs_info {int /*<<< orphan*/  super_for_commit; int /*<<< orphan*/  super_copy; int /*<<< orphan*/  free_space_root; int /*<<< orphan*/  uuid_root; int /*<<< orphan*/  quota_root; int /*<<< orphan*/  csum_root; int /*<<< orphan*/  dev_root; int /*<<< orphan*/  chunk_root; int /*<<< orphan*/  tree_root; int /*<<< orphan*/  extent_root; int /*<<< orphan*/  delayed_root; int /*<<< orphan*/  balance_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct btrfs_fs_info*) ; 

__attribute__((used)) static inline void free_fs_info(struct btrfs_fs_info *fs_info)
{
	kfree(fs_info->balance_ctl);
	kfree(fs_info->delayed_root);
	kfree(fs_info->extent_root);
	kfree(fs_info->tree_root);
	kfree(fs_info->chunk_root);
	kfree(fs_info->dev_root);
	kfree(fs_info->csum_root);
	kfree(fs_info->quota_root);
	kfree(fs_info->uuid_root);
	kfree(fs_info->free_space_root);
	kfree(fs_info->super_copy);
	kfree(fs_info->super_for_commit);
	kvfree(fs_info);
}