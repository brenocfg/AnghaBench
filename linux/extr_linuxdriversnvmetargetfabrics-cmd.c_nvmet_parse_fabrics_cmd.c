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
typedef  int u16 ;
struct nvmet_req {int /*<<< orphan*/  execute; int /*<<< orphan*/  data_len; struct nvme_command* cmd; } ;
struct TYPE_2__ {int fctype; } ;
struct nvme_command {TYPE_1__ fabrics; } ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_OPCODE ; 
#define  nvme_fabrics_type_property_get 129 
#define  nvme_fabrics_type_property_set 128 
 int /*<<< orphan*/  nvmet_execute_prop_get ; 
 int /*<<< orphan*/  nvmet_execute_prop_set ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

u16 nvmet_parse_fabrics_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;

	switch (cmd->fabrics.fctype) {
	case nvme_fabrics_type_property_set:
		req->data_len = 0;
		req->execute = nvmet_execute_prop_set;
		break;
	case nvme_fabrics_type_property_get:
		req->data_len = 0;
		req->execute = nvmet_execute_prop_get;
		break;
	default:
		pr_err("received unknown capsule type 0x%x\n",
			cmd->fabrics.fctype);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}

	return 0;
}