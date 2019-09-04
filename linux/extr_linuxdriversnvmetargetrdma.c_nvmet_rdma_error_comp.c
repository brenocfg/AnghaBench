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
struct TYPE_2__ {scalar_t__ ctrl; } ;
struct nvmet_rdma_queue {TYPE_1__ nvme_sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_ctrl_fatal_error (scalar_t__) ; 
 int /*<<< orphan*/  nvmet_rdma_queue_disconnect (struct nvmet_rdma_queue*) ; 

__attribute__((used)) static void nvmet_rdma_error_comp(struct nvmet_rdma_queue *queue)
{
	if (queue->nvme_sq.ctrl) {
		nvmet_ctrl_fatal_error(queue->nvme_sq.ctrl);
	} else {
		/*
		 * we didn't setup the controller yet in case
		 * of admin connect error, just disconnect and
		 * cleanup the queue
		 */
		nvmet_rdma_queue_disconnect(queue);
	}
}