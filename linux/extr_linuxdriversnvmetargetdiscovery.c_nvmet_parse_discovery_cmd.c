#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmet_req {int /*<<< orphan*/  execute; int /*<<< orphan*/  data_len; TYPE_2__* sq; struct nvme_command* cmd; } ;
struct TYPE_10__ {int opcode; } ;
struct TYPE_9__ {int cns; } ;
struct TYPE_8__ {int lid; } ;
struct nvme_command {TYPE_5__ common; TYPE_4__ identify; TYPE_3__ get_log_page; } ;
struct TYPE_7__ {TYPE_1__* ctrl; } ;
struct TYPE_6__ {int csts; } ;

/* Variables and functions */
 int NVME_CSTS_RDY ; 
 int /*<<< orphan*/  NVME_IDENTIFY_DATA_SIZE ; 
#define  NVME_ID_CNS_CTRL 131 
#define  NVME_LOG_DISC 130 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_OPCODE ; 
#define  nvme_admin_get_log_page 129 
#define  nvme_admin_identify 128 
 int /*<<< orphan*/  nvmet_execute_get_disc_log_page ; 
 int /*<<< orphan*/  nvmet_execute_identify_disc_ctrl ; 
 int /*<<< orphan*/  nvmet_get_log_page_len (struct nvme_command*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

u16 nvmet_parse_discovery_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;

	if (unlikely(!(req->sq->ctrl->csts & NVME_CSTS_RDY))) {
		pr_err("got cmd %d while not ready\n",
		       cmd->common.opcode);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}

	switch (cmd->common.opcode) {
	case nvme_admin_get_log_page:
		req->data_len = nvmet_get_log_page_len(cmd);

		switch (cmd->get_log_page.lid) {
		case NVME_LOG_DISC:
			req->execute = nvmet_execute_get_disc_log_page;
			return 0;
		default:
			pr_err("unsupported get_log_page lid %d\n",
			       cmd->get_log_page.lid);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		}
	case nvme_admin_identify:
		req->data_len = NVME_IDENTIFY_DATA_SIZE;
		switch (cmd->identify.cns) {
		case NVME_ID_CNS_CTRL:
			req->execute =
				nvmet_execute_identify_disc_ctrl;
			return 0;
		default:
			pr_err("unsupported identify cns %d\n",
			       cmd->identify.cns);
			return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		}
	default:
		pr_err("unsupported cmd %d\n", cmd->common.opcode);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}

	pr_err("unhandled cmd %d\n", cmd->common.opcode);
	return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
}