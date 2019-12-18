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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {TYPE_1__* transaction; struct btrfs_fs_info* fs_info; } ;
struct btrfs_qgroup_extent_record {int /*<<< orphan*/ * old_roots; scalar_t__ num_bytes; scalar_t__ bytenr; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int ENOMEM ; 
 int btrfs_qgroup_trace_extent_nolock (struct btrfs_fs_info*,struct btrfs_delayed_ref_root*,struct btrfs_qgroup_extent_record*) ; 
 int btrfs_qgroup_trace_extent_post (struct btrfs_fs_info*,struct btrfs_qgroup_extent_record*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_qgroup_extent_record*) ; 
 struct btrfs_qgroup_extent_record* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_qgroup_trace_extent(struct btrfs_trans_handle *trans, u64 bytenr,
			      u64 num_bytes, gfp_t gfp_flag)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_qgroup_extent_record *record;
	struct btrfs_delayed_ref_root *delayed_refs;
	int ret;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags)
	    || bytenr == 0 || num_bytes == 0)
		return 0;
	record = kzalloc(sizeof(*record), gfp_flag);
	if (!record)
		return -ENOMEM;

	delayed_refs = &trans->transaction->delayed_refs;
	record->bytenr = bytenr;
	record->num_bytes = num_bytes;
	record->old_roots = NULL;

	spin_lock(&delayed_refs->lock);
	ret = btrfs_qgroup_trace_extent_nolock(fs_info, delayed_refs, record);
	spin_unlock(&delayed_refs->lock);
	if (ret > 0) {
		kfree(record);
		return 0;
	}
	return btrfs_qgroup_trace_extent_post(fs_info, record);
}