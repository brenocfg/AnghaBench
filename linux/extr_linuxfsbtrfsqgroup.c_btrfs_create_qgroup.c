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
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_qgroup {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_ioctl_lock; int /*<<< orphan*/  qgroup_lock; struct btrfs_root* quota_root; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct btrfs_qgroup*) ; 
 int PTR_ERR (struct btrfs_qgroup*) ; 
 int add_qgroup_item (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 struct btrfs_qgroup* add_qgroup_rb (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct btrfs_qgroup* find_qgroup_rb (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_create_qgroup(struct btrfs_trans_handle *trans, u64 qgroupid)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_root *quota_root;
	struct btrfs_qgroup *qgroup;
	int ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	quota_root = fs_info->quota_root;
	if (!quota_root) {
		ret = -EINVAL;
		goto out;
	}
	qgroup = find_qgroup_rb(fs_info, qgroupid);
	if (qgroup) {
		ret = -EEXIST;
		goto out;
	}

	ret = add_qgroup_item(trans, quota_root, qgroupid);
	if (ret)
		goto out;

	spin_lock(&fs_info->qgroup_lock);
	qgroup = add_qgroup_rb(fs_info, qgroupid);
	spin_unlock(&fs_info->qgroup_lock);

	if (IS_ERR(qgroup))
		ret = PTR_ERR(qgroup);
out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	return ret;
}