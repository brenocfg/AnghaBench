#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct btrfs_fs_info {struct btrfs_balance_control* balance_ctl; } ;
struct TYPE_6__ {int flags; int target; } ;
struct TYPE_5__ {int flags; int target; } ;
struct TYPE_4__ {int flags; int target; } ;
struct btrfs_balance_control {TYPE_3__ meta; TYPE_2__ sys; TYPE_1__ data; } ;

/* Variables and functions */
 int BTRFS_BALANCE_ARGS_CONVERT ; 
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int BTRFS_BLOCK_GROUP_SYSTEM ; 

__attribute__((used)) static u64 get_restripe_target(struct btrfs_fs_info *fs_info, u64 flags)
{
	struct btrfs_balance_control *bctl = fs_info->balance_ctl;
	u64 target = 0;

	if (!bctl)
		return 0;

	if (flags & BTRFS_BLOCK_GROUP_DATA &&
	    bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT) {
		target = BTRFS_BLOCK_GROUP_DATA | bctl->data.target;
	} else if (flags & BTRFS_BLOCK_GROUP_SYSTEM &&
		   bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT) {
		target = BTRFS_BLOCK_GROUP_SYSTEM | bctl->sys.target;
	} else if (flags & BTRFS_BLOCK_GROUP_METADATA &&
		   bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT) {
		target = BTRFS_BLOCK_GROUP_METADATA | bctl->meta.target;
	}

	return target;
}