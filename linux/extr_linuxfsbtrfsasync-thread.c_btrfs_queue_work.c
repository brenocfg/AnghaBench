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
struct btrfs_workqueue {struct __btrfs_workqueue* normal; struct __btrfs_workqueue* high; } ;
struct btrfs_work {int /*<<< orphan*/  flags; } ;
struct __btrfs_workqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_HIGH_PRIO_BIT ; 
 int /*<<< orphan*/  __btrfs_queue_work (struct __btrfs_workqueue*,struct btrfs_work*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_queue_work(struct btrfs_workqueue *wq,
		      struct btrfs_work *work)
{
	struct __btrfs_workqueue *dest_wq;

	if (test_bit(WORK_HIGH_PRIO_BIT, &work->flags) && wq->high)
		dest_wq = wq->high;
	else
		dest_wq = wq->normal;
	__btrfs_queue_work(dest_wq, work);
}