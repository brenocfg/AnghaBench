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
struct ulist {int dummy; } ;
struct btrfs_qgroup_extent_record {struct ulist* old_roots; int /*<<< orphan*/  bytenr; } ;
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT ; 
 int btrfs_find_all_roots (int /*<<< orphan*/ *,struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ulist**,int) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,int) ; 

int btrfs_qgroup_trace_extent_post(struct btrfs_fs_info *fs_info,
				   struct btrfs_qgroup_extent_record *qrecord)
{
	struct ulist *old_root;
	u64 bytenr = qrecord->bytenr;
	int ret;

	ret = btrfs_find_all_roots(NULL, fs_info, bytenr, 0, &old_root, false);
	if (ret < 0) {
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		btrfs_warn(fs_info,
"error accounting new delayed refs extent (err code: %d), quota inconsistent",
			ret);
		return 0;
	}

	/*
	 * Here we don't need to get the lock of
	 * trans->transaction->delayed_refs, since inserted qrecord won't
	 * be deleted, only qrecord->node may be modified (new qrecord insert)
	 *
	 * So modifying qrecord->old_roots is safe here
	 */
	qrecord->old_roots = old_root;
	return 0;
}