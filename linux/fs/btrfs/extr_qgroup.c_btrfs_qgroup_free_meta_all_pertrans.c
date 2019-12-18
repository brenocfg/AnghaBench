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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_QGROUP_RSV_META_PERTRANS ; 
 int /*<<< orphan*/  btrfs_qgroup_free_refroot (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_qgroup_meta_free_all_pertrans (struct btrfs_root*) ; 

void btrfs_qgroup_free_meta_all_pertrans(struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) ||
	    !is_fstree(root->root_key.objectid))
		return;

	/* TODO: Update trace point to handle such free */
	trace_qgroup_meta_free_all_pertrans(root);
	/* Special value -1 means to free all reserved space */
	btrfs_qgroup_free_refroot(fs_info, root->root_key.objectid, (u64)-1,
				  BTRFS_QGROUP_RSV_META_PERTRANS);
}