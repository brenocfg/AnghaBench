#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knav_range_info {TYPE_1__* ops; } ;
struct knav_queue_inst {TYPE_2__* kdev; struct knav_range_info* range; } ;
struct knav_queue {int /*<<< orphan*/  stats; int /*<<< orphan*/  list; int /*<<< orphan*/  notifier_enabled; struct knav_queue_inst* inst; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close_queue ) (struct knav_range_info*,struct knav_queue_inst*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct knav_queue*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_dev_lock ; 
 int /*<<< orphan*/  knav_queue_disable_notifier (struct knav_queue*) ; 
 int /*<<< orphan*/  knav_queue_is_busy (struct knav_queue_inst*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct knav_range_info*,struct knav_queue_inst*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void knav_queue_close(void *qhandle)
{
	struct knav_queue *qh = qhandle;
	struct knav_queue_inst *inst = qh->inst;

	while (atomic_read(&qh->notifier_enabled) > 0)
		knav_queue_disable_notifier(qh);

	mutex_lock(&knav_dev_lock);
	list_del_rcu(&qh->list);
	mutex_unlock(&knav_dev_lock);
	synchronize_rcu();
	if (!knav_queue_is_busy(inst)) {
		struct knav_range_info *range = inst->range;

		if (range->ops && range->ops->close_queue)
			range->ops->close_queue(range, inst);
	}
	free_percpu(qh->stats);
	devm_kfree(inst->kdev->dev, qh);
}