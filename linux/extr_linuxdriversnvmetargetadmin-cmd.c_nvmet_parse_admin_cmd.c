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
typedef  int u16 ;
struct nvmet_req {TYPE_4__* sq; int /*<<< orphan*/  data_len; void* execute; struct nvme_command* cmd; } ;
struct TYPE_7__ {int opcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  cns; } ;
struct TYPE_5__ {int /*<<< orphan*/  lid; } ;
struct nvme_command {TYPE_3__ common; TYPE_2__ identify; TYPE_1__ get_log_page; } ;
struct TYPE_8__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_IDENTIFY_DATA_SIZE ; 
#define  NVME_ID_CNS_CTRL 144 
#define  NVME_ID_CNS_NS 143 
#define  NVME_ID_CNS_NS_ACTIVE_LIST 142 
#define  NVME_ID_CNS_NS_DESC_LIST 141 
#define  NVME_LOG_ANA 140 
#define  NVME_LOG_CHANGED_NS 139 
#define  NVME_LOG_CMD_EFFECTS 138 
#define  NVME_LOG_ERROR 137 
#define  NVME_LOG_FW_SLOT 136 
#define  NVME_LOG_SMART 135 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_OPCODE ; 
#define  nvme_admin_abort_cmd 134 
#define  nvme_admin_async_event 133 
#define  nvme_admin_get_features 132 
#define  nvme_admin_get_log_page 131 
#define  nvme_admin_identify 130 
#define  nvme_admin_keep_alive 129 
#define  nvme_admin_set_features 128 
 int nvmet_check_ctrl_status (struct nvmet_req*,struct nvme_command*) ; 
 void* nvmet_execute_abort ; 
 void* nvmet_execute_async_event ; 
 void* nvmet_execute_get_features ; 
 void* nvmet_execute_get_log_changed_ns ; 
 void* nvmet_execute_get_log_cmd_effects_ns ; 
 void* nvmet_execute_get_log_page_ana ; 
 void* nvmet_execute_get_log_page_noop ; 
 void* nvmet_execute_get_log_page_smart ; 
 void* nvmet_execute_identify_ctrl ; 
 void* nvmet_execute_identify_desclist ; 
 void* nvmet_execute_identify_ns ; 
 void* nvmet_execute_identify_nslist ; 
 void* nvmet_execute_keep_alive ; 
 void* nvmet_execute_set_features ; 
 int /*<<< orphan*/  nvmet_get_log_page_len (struct nvme_command*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

u16 nvmet_parse_admin_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;
	u16 ret;

	ret = nvmet_check_ctrl_status(req, cmd);
	if (unlikely(ret))
		return ret;

	switch (cmd->common.opcode) {
	case nvme_admin_get_log_page:
		req->data_len = nvmet_get_log_page_len(cmd);

		switch (cmd->get_log_page.lid) {
		case NVME_LOG_ERROR:
			/*
			 * We currently never set the More bit in the status
			 * field, so all error log entries are invalid and can
			 * be zeroed out.  This is called a minum viable
			 * implementation (TM) of this mandatory log page.
			 */
			req->execute = nvmet_execute_get_log_page_noop;
			return 0;
		case NVME_LOG_SMART:
			req->execute = nvmet_execute_get_log_page_smart;
			return 0;
		case NVME_LOG_FW_SLOT:
			/*
			 * We only support a single firmware slot which always
			 * is active, so we can zero out the whole firmware slot
			 * log and still claim to fully implement this mandatory
			 * log page.
			 */
			req->execute = nvmet_execute_get_log_page_noop;
			return 0;
		case NVME_LOG_CHANGED_NS:
			req->execute = nvmet_execute_get_log_changed_ns;
			return 0;
		case NVME_LOG_CMD_EFFECTS:
			req->execute = nvmet_execute_get_log_cmd_effects_ns;
			return 0;
		case NVME_LOG_ANA:
			req->execute = nvmet_execute_get_log_page_ana;
			return 0;
		}
		break;
	case nvme_admin_identify:
		req->data_len = NVME_IDENTIFY_DATA_SIZE;
		switch (cmd->identify.cns) {
		case NVME_ID_CNS_NS:
			req->execute = nvmet_execute_identify_ns;
			return 0;
		case NVME_ID_CNS_CTRL:
			req->execute = nvmet_execute_identify_ctrl;
			return 0;
		case NVME_ID_CNS_NS_ACTIVE_LIST:
			req->execute = nvmet_execute_identify_nslist;
			return 0;
		case NVME_ID_CNS_NS_DESC_LIST:
			req->execute = nvmet_execute_identify_desclist;
			return 0;
		}
		break;
	case nvme_admin_abort_cmd:
		req->execute = nvmet_execute_abort;
		req->data_len = 0;
		return 0;
	case nvme_admin_set_features:
		req->execute = nvmet_execute_set_features;
		req->data_len = 0;
		return 0;
	case nvme_admin_get_features:
		req->execute = nvmet_execute_get_features;
		req->data_len = 0;
		return 0;
	case nvme_admin_async_event:
		req->execute = nvmet_execute_async_event;
		req->data_len = 0;
		return 0;
	case nvme_admin_keep_alive:
		req->execute = nvmet_execute_keep_alive;
		req->data_len = 0;
		return 0;
	}

	pr_err("unhandled cmd %d on qid %d\n", cmd->common.opcode,
	       req->sq->qid);
	return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
}