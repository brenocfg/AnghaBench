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
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  nodesize; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum btrfs_qgroup_rsv_type { ____Placeholder_btrfs_qgroup_rsv_type } btrfs_qgroup_rsv_type ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  add_root_meta_rsv (struct btrfs_root*,int,int) ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int qgroup_reserve (struct btrfs_root*,int,int,int) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_qgroup_meta_reserve (struct btrfs_root*,int /*<<< orphan*/ ,int) ; 

int __btrfs_qgroup_reserve_meta(struct btrfs_root *root, int num_bytes,
				enum btrfs_qgroup_rsv_type type, bool enforce)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int ret;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid) || num_bytes == 0)
		return 0;

	BUG_ON(num_bytes != round_down(num_bytes, fs_info->nodesize));
	trace_qgroup_meta_reserve(root, (s64)num_bytes, type);
	ret = qgroup_reserve(root, num_bytes, enforce, type);
	if (ret < 0)
		return ret;
	/*
	 * Record what we have reserved into root.
	 *
	 * To avoid quota disabled->enabled underflow.
	 * In that case, we may try to free space we haven't reserved
	 * (since quota was disabled), so record what we reserved into root.
	 * And ensure later release won't underflow this number.
	 */
	add_root_meta_rsv(root, num_bytes, type);
	return ret;
}