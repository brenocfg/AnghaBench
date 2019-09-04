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
struct btrfs_qgroup {int /*<<< orphan*/  node; } ;
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_tree; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __del_qgroup_rb (struct btrfs_qgroup*) ; 
 struct btrfs_qgroup* find_qgroup_rb (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int del_qgroup_rb(struct btrfs_fs_info *fs_info, u64 qgroupid)
{
	struct btrfs_qgroup *qgroup = find_qgroup_rb(fs_info, qgroupid);

	if (!qgroup)
		return -ENOENT;

	rb_erase(&qgroup->node, &fs_info->qgroup_tree);
	__del_qgroup_rb(qgroup);
	return 0;
}