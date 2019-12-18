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
struct TYPE_2__ {int /*<<< orphan*/  replace_wait; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  lock_finishing_cancel_unmount; } ;
struct btrfs_fs_info {TYPE_1__ dev_replace; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_init_dev_replace_locks(struct btrfs_fs_info *fs_info)
{
	mutex_init(&fs_info->dev_replace.lock_finishing_cancel_unmount);
	init_rwsem(&fs_info->dev_replace.rwsem);
	init_waitqueue_head(&fs_info->dev_replace.replace_wait);
}