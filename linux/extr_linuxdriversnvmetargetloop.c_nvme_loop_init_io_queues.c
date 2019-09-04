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
struct nvmf_ctrl_options {int /*<<< orphan*/  nr_io_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_count; int /*<<< orphan*/  device; struct nvmf_ctrl_options* opts; } ;
struct nvme_loop_ctrl {TYPE_2__ ctrl; TYPE_1__* queues; } ;
struct TYPE_3__ {int /*<<< orphan*/  nvme_sq; struct nvme_loop_ctrl* ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  nvme_loop_destroy_io_queues (struct nvme_loop_ctrl*) ; 
 int nvme_set_queue_count (TYPE_2__*,unsigned int*) ; 
 int nvmet_sq_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_loop_init_io_queues(struct nvme_loop_ctrl *ctrl)
{
	struct nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	unsigned int nr_io_queues;
	int ret, i;

	nr_io_queues = min(opts->nr_io_queues, num_online_cpus());
	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	if (ret || !nr_io_queues)
		return ret;

	dev_info(ctrl->ctrl.device, "creating %d I/O queues.\n", nr_io_queues);

	for (i = 1; i <= nr_io_queues; i++) {
		ctrl->queues[i].ctrl = ctrl;
		ret = nvmet_sq_init(&ctrl->queues[i].nvme_sq);
		if (ret)
			goto out_destroy_queues;

		ctrl->ctrl.queue_count++;
	}

	return 0;

out_destroy_queues:
	nvme_loop_destroy_io_queues(ctrl);
	return ret;
}