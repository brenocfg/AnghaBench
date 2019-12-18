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
 int /*<<< orphan*/  btrfs_qgroup_free_refroot (struct btrfs_fs_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int sub_root_meta_rsv (struct btrfs_root*,int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_qgroup_meta_reserve (struct btrfs_root*,int /*<<< orphan*/ ,int) ; 

void __btrfs_qgroup_free_meta(struct btrfs_root *root, int num_bytes,
			      enum btrfs_qgroup_rsv_type type)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		return;

	/*
	 * reservation for META_PREALLOC can happen before quota is enabled,
	 * which can lead to underflow.
	 * Here ensure we will only free what we really have reserved.
	 */
	num_bytes = sub_root_meta_rsv(root, num_bytes, type);
	BUG_ON(num_bytes != round_down(num_bytes, fs_info->nodesize));
	trace_qgroup_meta_reserve(root, -(s64)num_bytes, type);
	btrfs_qgroup_free_refroot(fs_info, root->root_key.objectid,
				  num_bytes, type);
}