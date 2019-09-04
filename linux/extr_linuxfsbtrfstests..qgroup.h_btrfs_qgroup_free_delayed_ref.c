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
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_QGROUP_RSV_DATA ; 
 int /*<<< orphan*/  btrfs_qgroup_free_refroot (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_qgroup_free_delayed_ref (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_qgroup_free_delayed_ref(struct btrfs_fs_info *fs_info,
						 u64 ref_root, u64 num_bytes)
{
	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		return;
	trace_btrfs_qgroup_free_delayed_ref(fs_info, ref_root, num_bytes);
	btrfs_qgroup_free_refroot(fs_info, ref_root, num_bytes,
				  BTRFS_QGROUP_RSV_DATA);
}