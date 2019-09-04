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
struct TYPE_3__ {int queue_count; } ;
struct nvme_loop_ctrl {TYPE_2__* queues; TYPE_1__ ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_LOOP_Q_LIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_sq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_loop_destroy_io_queues(struct nvme_loop_ctrl *ctrl)
{
	int i;

	for (i = 1; i < ctrl->ctrl.queue_count; i++) {
		clear_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[i].flags);
		nvmet_sq_destroy(&ctrl->queues[i].nvme_sq);
	}
}