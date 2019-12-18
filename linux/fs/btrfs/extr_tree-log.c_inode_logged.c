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
struct btrfs_trans_handle {scalar_t__ transid; TYPE_1__* fs_info; } ;
struct btrfs_inode {scalar_t__ logged_trans; scalar_t__ last_trans; int /*<<< orphan*/  runtime_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_LOG_RECOVERING ; 
 int /*<<< orphan*/  BTRFS_INODE_NEEDS_FULL_SYNC ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool inode_logged(struct btrfs_trans_handle *trans,
			 struct btrfs_inode *inode)
{
	if (inode->logged_trans == trans->transid)
		return true;

	if (inode->last_trans == trans->transid &&
	    test_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runtime_flags) &&
	    !test_bit(BTRFS_FS_LOG_RECOVERING, &trans->fs_info->flags))
		return true;

	return false;
}