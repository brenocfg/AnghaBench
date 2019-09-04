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
struct nvme_request {int flags; TYPE_3__* cmd; } ;
struct nvme_ctrl {int state; } ;
struct TYPE_5__ {int /*<<< orphan*/  fctype; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {TYPE_2__ fabrics; TYPE_1__ common; } ;

/* Variables and functions */
#define  NVME_CTRL_CONNECTING 130 
#define  NVME_CTRL_DEAD 129 
#define  NVME_CTRL_NEW 128 
 int NVME_REQ_USERCMD ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  nvme_fabrics_command ; 
 int /*<<< orphan*/  nvme_fabrics_type_connect ; 
 struct nvme_request* nvme_req (struct request*) ; 

bool __nvmf_check_ready(struct nvme_ctrl *ctrl, struct request *rq,
		bool queue_live)
{
	struct nvme_request *req = nvme_req(rq);

	/*
	 * If we are in some state of setup or teardown only allow
	 * internally generated commands.
	 */
	if (!blk_rq_is_passthrough(rq) || (req->flags & NVME_REQ_USERCMD))
		return false;

	/*
	 * Only allow commands on a live queue, except for the connect command,
	 * which is require to set the queue live in the appropinquate states.
	 */
	switch (ctrl->state) {
	case NVME_CTRL_NEW:
	case NVME_CTRL_CONNECTING:
		if (req->cmd->common.opcode == nvme_fabrics_command &&
		    req->cmd->fabrics.fctype == nvme_fabrics_type_connect)
			return true;
		break;
	default:
		break;
	case NVME_CTRL_DEAD:
		return false;
	}

	return queue_live;
}