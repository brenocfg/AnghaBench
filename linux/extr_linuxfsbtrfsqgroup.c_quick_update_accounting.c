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
struct btrfs_qgroup {scalar_t__ excl; scalar_t__ rfer; } ;
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT ; 
 int __qgroup_excl_accounting (struct btrfs_fs_info*,struct ulist*,int /*<<< orphan*/ ,struct btrfs_qgroup*,int) ; 
 struct btrfs_qgroup* find_qgroup_rb (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int quick_update_accounting(struct btrfs_fs_info *fs_info,
				   struct ulist *tmp, u64 src, u64 dst,
				   int sign)
{
	struct btrfs_qgroup *qgroup;
	int ret = 1;
	int err = 0;

	qgroup = find_qgroup_rb(fs_info, src);
	if (!qgroup)
		goto out;
	if (qgroup->excl == qgroup->rfer) {
		ret = 0;
		err = __qgroup_excl_accounting(fs_info, tmp, dst,
					       qgroup, sign);
		if (err < 0) {
			ret = err;
			goto out;
		}
	}
out:
	if (ret)
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	return ret;
}