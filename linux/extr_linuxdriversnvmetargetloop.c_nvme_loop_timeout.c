#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct nvme_loop_iod {TYPE_2__* queue; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_6__ {int status; } ;
struct TYPE_5__ {TYPE_1__* ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int NVME_SC_ABORT_REQ ; 
 int NVME_SC_DNR ; 
 struct nvme_loop_iod* blk_mq_rq_to_pdu (struct request*) ; 
 TYPE_3__* nvme_req (struct request*) ; 
 int /*<<< orphan*/  nvme_reset_ctrl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum blk_eh_timer_return
nvme_loop_timeout(struct request *rq, bool reserved)
{
	struct nvme_loop_iod *iod = blk_mq_rq_to_pdu(rq);

	/* queue error recovery */
	nvme_reset_ctrl(&iod->queue->ctrl->ctrl);

	/* fail with DNR on admin cmd timeout */
	nvme_req(rq)->status = NVME_SC_ABORT_REQ | NVME_SC_DNR;

	return BLK_EH_DONE;
}