#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct nvme_dev {TYPE_1__ ctrl; int /*<<< orphan*/  remove_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvme_dev_disable (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_get_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_kill_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_put_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_remove_dead_ctrl(struct nvme_dev *dev, int status)
{
	dev_warn(dev->ctrl.device, "Removing after probe failure status: %d\n", status);

	nvme_get_ctrl(&dev->ctrl);
	nvme_dev_disable(dev, false);
	nvme_kill_queues(&dev->ctrl);
	if (!queue_work(nvme_wq, &dev->remove_work))
		nvme_put_ctrl(&dev->ctrl);
}