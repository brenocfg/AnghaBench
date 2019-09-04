#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct nvmet_subsys {int /*<<< orphan*/  max_qid; } ;
struct nvmet_req {TYPE_4__* sq; TYPE_2__* cmd; } ;
struct TYPE_8__ {TYPE_3__* ctrl; } ;
struct TYPE_7__ {int kato; int /*<<< orphan*/  aen_enabled; struct nvmet_subsys* subsys; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cdw10; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int NVMET_AEN_CFG_ALL ; 
#define  NVME_FEAT_ASYNC_EVENT 132 
#define  NVME_FEAT_HOST_ID 131 
#define  NVME_FEAT_KATO 130 
#define  NVME_FEAT_NUM_QUEUES 129 
#define  NVME_FEAT_WRITE_PROTECT 128 
 int NVME_SC_CMD_SEQ_ERROR ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int nvmet_set_feat_write_protect (struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_execute_set_features(struct nvmet_req *req)
{
	struct nvmet_subsys *subsys = req->sq->ctrl->subsys;
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10[0]);
	u32 val32;
	u16 status = 0;

	switch (cdw10 & 0xff) {
	case NVME_FEAT_NUM_QUEUES:
		nvmet_set_result(req,
			(subsys->max_qid - 1) | ((subsys->max_qid - 1) << 16));
		break;
	case NVME_FEAT_KATO:
		val32 = le32_to_cpu(req->cmd->common.cdw10[1]);
		req->sq->ctrl->kato = DIV_ROUND_UP(val32, 1000);
		nvmet_set_result(req, req->sq->ctrl->kato);
		break;
	case NVME_FEAT_ASYNC_EVENT:
		val32 = le32_to_cpu(req->cmd->common.cdw10[1]);
		if (val32 & ~NVMET_AEN_CFG_ALL) {
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			break;
		}

		WRITE_ONCE(req->sq->ctrl->aen_enabled, val32);
		nvmet_set_result(req, val32);
		break;
	case NVME_FEAT_HOST_ID:
		status = NVME_SC_CMD_SEQ_ERROR | NVME_SC_DNR;
		break;
	case NVME_FEAT_WRITE_PROTECT:
		status = nvmet_set_feat_write_protect(req);
		break;
	default:
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		break;
	}

	nvmet_req_complete(req, status);
}