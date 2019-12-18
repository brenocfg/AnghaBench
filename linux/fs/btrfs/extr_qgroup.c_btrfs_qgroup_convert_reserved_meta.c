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
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_QGROUP_RSV_META_PREALLOC ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qgroup_convert_meta (struct btrfs_fs_info*,int /*<<< orphan*/ ,int) ; 
 int sub_root_meta_rsv (struct btrfs_root*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_qgroup_meta_convert (struct btrfs_root*,int) ; 

void btrfs_qgroup_convert_reserved_meta(struct btrfs_root *root, int num_bytes)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		return;
	/* Same as btrfs_qgroup_free_meta_prealloc() */
	num_bytes = sub_root_meta_rsv(root, num_bytes,
				      BTRFS_QGROUP_RSV_META_PREALLOC);
	trace_qgroup_meta_convert(root, num_bytes);
	qgroup_convert_meta(fs_info, root->root_key.objectid, num_bytes);
}