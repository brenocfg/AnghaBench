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
struct TYPE_2__ {int /*<<< orphan*/  read_lock_wq; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_finishing_cancel_unmount; } ;
struct btrfs_fs_info {TYPE_1__ dev_replace; int /*<<< orphan*/  replace_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_init_dev_replace_locks(struct btrfs_fs_info *fs_info)
{
	mutex_init(&fs_info->dev_replace.lock_finishing_cancel_unmount);
	rwlock_init(&fs_info->dev_replace.lock);
	atomic_set(&fs_info->dev_replace.read_locks, 0);
	atomic_set(&fs_info->dev_replace.blocking_readers, 0);
	init_waitqueue_head(&fs_info->replace_wait);
	init_waitqueue_head(&fs_info->dev_replace.read_lock_wq);
}