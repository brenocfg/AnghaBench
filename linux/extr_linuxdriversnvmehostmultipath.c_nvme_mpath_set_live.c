#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns_head {int /*<<< orphan*/  requeue_work; TYPE_1__* subsys; TYPE_3__* disk; int /*<<< orphan*/  lock; } ;
struct nvme_ns {struct nvme_ns_head* head; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_add_disk (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* disk_to_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ns_id_attr_group ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_mpath_set_live(struct nvme_ns *ns)
{
	struct nvme_ns_head *head = ns->head;

	lockdep_assert_held(&ns->head->lock);

	if (!head->disk)
		return;

	if (!(head->disk->flags & GENHD_FL_UP)) {
		device_add_disk(&head->subsys->dev, head->disk);
		if (sysfs_create_group(&disk_to_dev(head->disk)->kobj,
				&nvme_ns_id_attr_group))
			dev_warn(&head->subsys->dev,
				 "failed to create id group.\n");
	}

	kblockd_schedule_work(&ns->head->requeue_work);
}