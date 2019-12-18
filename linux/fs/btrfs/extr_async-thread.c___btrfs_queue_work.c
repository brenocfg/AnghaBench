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
struct btrfs_work {int /*<<< orphan*/  normal_work; int /*<<< orphan*/  ordered_list; scalar_t__ ordered_func; struct __btrfs_workqueue* wq; } ;
struct __btrfs_workqueue {int /*<<< orphan*/  normal_wq; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  ordered_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  thresh_queue_hook (struct __btrfs_workqueue*) ; 
 int /*<<< orphan*/  trace_btrfs_work_queued (struct btrfs_work*) ; 

__attribute__((used)) static inline void __btrfs_queue_work(struct __btrfs_workqueue *wq,
				      struct btrfs_work *work)
{
	unsigned long flags;

	work->wq = wq;
	thresh_queue_hook(wq);
	if (work->ordered_func) {
		spin_lock_irqsave(&wq->list_lock, flags);
		list_add_tail(&work->ordered_list, &wq->ordered_list);
		spin_unlock_irqrestore(&wq->list_lock, flags);
	}
	trace_btrfs_work_queued(work);
	queue_work(wq->normal_wq, &work->normal_work);
}