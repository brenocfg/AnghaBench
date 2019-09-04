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
struct request {int cmd_flags; } ;
struct nvme_ctrl {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 scalar_t__ NVME_CTRL_DEAD ; 
 scalar_t__ NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  NVME_SC_HOST_PATH_ERROR ; 
 int REQ_NVME_MPATH ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_noretry_request (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 TYPE_1__* nvme_req (struct request*) ; 

blk_status_t nvmf_fail_nonready_command(struct nvme_ctrl *ctrl,
		struct request *rq)
{
	if (ctrl->state != NVME_CTRL_DELETING &&
	    ctrl->state != NVME_CTRL_DEAD &&
	    !blk_noretry_request(rq) && !(rq->cmd_flags & REQ_NVME_MPATH))
		return BLK_STS_RESOURCE;

	nvme_req(rq)->status = NVME_SC_HOST_PATH_ERROR;
	blk_mq_start_request(rq);
	nvme_complete_rq(rq);
	return BLK_STS_OK;
}