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
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_ioctl_lock; } ;

/* Variables and functions */
 int __del_qgroup_relation (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_del_qgroup_relation(struct btrfs_trans_handle *trans, u64 src,
			      u64 dst)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	int ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	ret = __del_qgroup_relation(trans, src, dst);
	mutex_unlock(&fs_info->qgroup_ioctl_lock);

	return ret;
}