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
struct TYPE_2__ {scalar_t__* values; } ;
struct btrfs_qgroup {TYPE_1__ rsv; int /*<<< orphan*/  qgroupid; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum btrfs_qgroup_rsv_type { ____Placeholder_btrfs_qgroup_rsv_type } btrfs_qgroup_rsv_type ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_RATELIMIT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qgroup_rsv_type_str (int) ; 
 int /*<<< orphan*/  trace_qgroup_update_reserve (struct btrfs_fs_info*,struct btrfs_qgroup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qgroup_rsv_release(struct btrfs_fs_info *fs_info,
			       struct btrfs_qgroup *qgroup, u64 num_bytes,
			       enum btrfs_qgroup_rsv_type type)
{
	trace_qgroup_update_reserve(fs_info, qgroup, -(s64)num_bytes, type);
	if (qgroup->rsv.values[type] >= num_bytes) {
		qgroup->rsv.values[type] -= num_bytes;
		return;
	}
#ifdef CONFIG_BTRFS_DEBUG
	WARN_RATELIMIT(1,
		"qgroup %llu %s reserved space underflow, have %llu to free %llu",
		qgroup->qgroupid, qgroup_rsv_type_str(type),
		qgroup->rsv.values[type], num_bytes);
#endif
	qgroup->rsv.values[type] = 0;
}