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
typedef  int u16 ;
struct nvmf_connect_data {int dummy; } ;
struct nvmet_req {int data_len; int /*<<< orphan*/  execute; struct nvme_command* cmd; } ;
struct TYPE_4__ {scalar_t__ qid; } ;
struct TYPE_6__ {scalar_t__ opcode; scalar_t__ fctype; } ;
struct TYPE_5__ {scalar_t__ opcode; } ;
struct nvme_command {TYPE_1__ connect; TYPE_3__ fabrics; TYPE_2__ common; } ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_OPCODE ; 
 scalar_t__ nvme_fabrics_command ; 
 scalar_t__ nvme_fabrics_type_connect ; 
 int /*<<< orphan*/  nvmet_execute_admin_connect ; 
 int /*<<< orphan*/  nvmet_execute_io_connect ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

u16 nvmet_parse_connect_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;

	if (cmd->common.opcode != nvme_fabrics_command) {
		pr_err("invalid command 0x%x on unconnected queue.\n",
			cmd->fabrics.opcode);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}
	if (cmd->fabrics.fctype != nvme_fabrics_type_connect) {
		pr_err("invalid capsule type 0x%x on unconnected queue.\n",
			cmd->fabrics.fctype);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}

	req->data_len = sizeof(struct nvmf_connect_data);
	if (cmd->connect.qid == 0)
		req->execute = nvmet_execute_admin_connect;
	else
		req->execute = nvmet_execute_io_connect;
	return 0;
}