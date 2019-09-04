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
struct TYPE_7__ {int kato; int /*<<< orphan*/  hostid; int /*<<< orphan*/  aen_enabled; struct nvmet_subsys* subsys; } ;
struct TYPE_5__ {int* cdw10; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
#define  NVME_FEAT_ASYNC_EVENT 133 
#define  NVME_FEAT_HOST_ID 132 
#define  NVME_FEAT_KATO 131 
#define  NVME_FEAT_NUM_QUEUES 130 
#define  NVME_FEAT_VOLATILE_WC 129 
#define  NVME_FEAT_WRITE_PROTECT 128 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int) ; 
 int le32_to_cpu (int) ; 
 int nvmet_copy_to_sgl (struct nvmet_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int nvmet_get_feat_write_protect (struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_execute_get_features(struct nvmet_req *req)
{
	struct nvmet_subsys *subsys = req->sq->ctrl->subsys;
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10[0]);
	u16 status = 0;

	switch (cdw10 & 0xff) {
	/*
	 * These features are mandatory in the spec, but we don't
	 * have a useful way to implement them.  We'll eventually
	 * need to come up with some fake values for these.
	 */
#if 0
	case NVME_FEAT_ARBITRATION:
		break;
	case NVME_FEAT_POWER_MGMT:
		break;
	case NVME_FEAT_TEMP_THRESH:
		break;
	case NVME_FEAT_ERR_RECOVERY:
		break;
	case NVME_FEAT_IRQ_COALESCE:
		break;
	case NVME_FEAT_IRQ_CONFIG:
		break;
	case NVME_FEAT_WRITE_ATOMIC:
		break;
#endif
	case NVME_FEAT_ASYNC_EVENT:
		nvmet_set_result(req, READ_ONCE(req->sq->ctrl->aen_enabled));
		break;
	case NVME_FEAT_VOLATILE_WC:
		nvmet_set_result(req, 1);
		break;
	case NVME_FEAT_NUM_QUEUES:
		nvmet_set_result(req,
			(subsys->max_qid-1) | ((subsys->max_qid-1) << 16));
		break;
	case NVME_FEAT_KATO:
		nvmet_set_result(req, req->sq->ctrl->kato * 1000);
		break;
	case NVME_FEAT_HOST_ID:
		/* need 128-bit host identifier flag */
		if (!(req->cmd->common.cdw10[1] & cpu_to_le32(1 << 0))) {
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			break;
		}

		status = nvmet_copy_to_sgl(req, 0, &req->sq->ctrl->hostid,
				sizeof(req->sq->ctrl->hostid));
		break;
	case NVME_FEAT_WRITE_PROTECT:
		status = nvmet_get_feat_write_protect(req);
		break;
	default:
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		break;
	}

	nvmet_req_complete(req, status);
}