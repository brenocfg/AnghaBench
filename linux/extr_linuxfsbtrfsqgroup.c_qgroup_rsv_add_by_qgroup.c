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
struct TYPE_2__ {int /*<<< orphan*/ * values; } ;
struct btrfs_qgroup {TYPE_1__ rsv; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int BTRFS_QGROUP_RSV_LAST ; 
 int /*<<< orphan*/  qgroup_rsv_add (struct btrfs_fs_info*,struct btrfs_qgroup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qgroup_rsv_add_by_qgroup(struct btrfs_fs_info *fs_info,
				     struct btrfs_qgroup *dest,
				     struct btrfs_qgroup *src)
{
	int i;

	for (i = 0; i < BTRFS_QGROUP_RSV_LAST; i++)
		qgroup_rsv_add(fs_info, dest, src->rsv.values[i], i);
}