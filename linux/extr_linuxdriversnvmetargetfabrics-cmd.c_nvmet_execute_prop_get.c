#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct nvmet_req {TYPE_6__* rsp; TYPE_3__* cmd; TYPE_1__* sq; } ;
struct nvmet_ctrl {int /*<<< orphan*/  csts; int /*<<< orphan*/  cc; TYPE_4__* subsys; int /*<<< orphan*/  cap; } ;
struct TYPE_11__ {int /*<<< orphan*/  u64; } ;
struct TYPE_12__ {TYPE_5__ result; } ;
struct TYPE_10__ {int /*<<< orphan*/  ver; } ;
struct TYPE_8__ {int attrib; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {TYPE_2__ prop_get; } ;
struct TYPE_7__ {struct nvmet_ctrl* ctrl; } ;

/* Variables and functions */
#define  NVME_REG_CAP 131 
#define  NVME_REG_CC 130 
#define  NVME_REG_CSTS 129 
#define  NVME_REG_VS 128 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_execute_prop_get(struct nvmet_req *req)
{
	struct nvmet_ctrl *ctrl = req->sq->ctrl;
	u16 status = 0;
	u64 val = 0;

	if (req->cmd->prop_get.attrib & 1) {
		switch (le32_to_cpu(req->cmd->prop_get.offset)) {
		case NVME_REG_CAP:
			val = ctrl->cap;
			break;
		default:
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			break;
		}
	} else {
		switch (le32_to_cpu(req->cmd->prop_get.offset)) {
		case NVME_REG_VS:
			val = ctrl->subsys->ver;
			break;
		case NVME_REG_CC:
			val = ctrl->cc;
			break;
		case NVME_REG_CSTS:
			val = ctrl->csts;
			break;
		default:
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			break;
		}
	}

	req->rsp->result.u64 = cpu_to_le64(val);
	nvmet_req_complete(req, status);
}