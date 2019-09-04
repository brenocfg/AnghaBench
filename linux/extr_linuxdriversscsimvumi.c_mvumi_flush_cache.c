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
struct mvumi_msg_frame {unsigned char device_id; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  cdb_length; scalar_t__ data_transfer_length; int /*<<< orphan*/  cmd_flag; int /*<<< orphan*/  req_function; } ;
struct mvumi_hba {unsigned char max_target_id; int* target_map; TYPE_1__* pdev; } ;
struct mvumi_cmd {scalar_t__ cmd_status; struct mvumi_msg_frame* frame; int /*<<< orphan*/  sync_cmd; int /*<<< orphan*/ * scmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_CORE_MODULE ; 
 int /*<<< orphan*/  CDB_CORE_SHUTDOWN ; 
 int /*<<< orphan*/  CL_FUN_SCSI_CMD ; 
 int /*<<< orphan*/  CMD_FLAG_NON_DATA ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 scalar_t__ REQ_STATUS_PENDING ; 
 scalar_t__ SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SCSI_CMD_MARVELL_SPECIFIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvumi_cmd* mvumi_create_internal_cmd (struct mvumi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvumi_delete_internal_cmd (struct mvumi_hba*,struct mvumi_cmd*) ; 
 int /*<<< orphan*/  mvumi_issue_blocked_cmd (struct mvumi_hba*,struct mvumi_cmd*) ; 

__attribute__((used)) static unsigned char mvumi_flush_cache(struct mvumi_hba *mhba)
{
	struct mvumi_cmd *cmd;
	struct mvumi_msg_frame *frame;
	unsigned char device_id, retry = 0;
	unsigned char bitcount = sizeof(unsigned char) * 8;

	for (device_id = 0; device_id < mhba->max_target_id; device_id++) {
		if (!(mhba->target_map[device_id / bitcount] &
				(1 << (device_id % bitcount))))
			continue;
get_cmd:	cmd = mvumi_create_internal_cmd(mhba, 0);
		if (!cmd) {
			if (retry++ >= 5) {
				dev_err(&mhba->pdev->dev, "failed to get memory"
					" for internal flush cache cmd for "
					"device %d", device_id);
				retry = 0;
				continue;
			} else
				goto get_cmd;
		}
		cmd->scmd = NULL;
		cmd->cmd_status = REQ_STATUS_PENDING;
		atomic_set(&cmd->sync_cmd, 0);
		frame = cmd->frame;
		frame->req_function = CL_FUN_SCSI_CMD;
		frame->device_id = device_id;
		frame->cmd_flag = CMD_FLAG_NON_DATA;
		frame->data_transfer_length = 0;
		frame->cdb_length = MAX_COMMAND_SIZE;
		memset(frame->cdb, 0, MAX_COMMAND_SIZE);
		frame->cdb[0] = SCSI_CMD_MARVELL_SPECIFIC;
		frame->cdb[1] = CDB_CORE_MODULE;
		frame->cdb[2] = CDB_CORE_SHUTDOWN;

		mvumi_issue_blocked_cmd(mhba, cmd);
		if (cmd->cmd_status != SAM_STAT_GOOD) {
			dev_err(&mhba->pdev->dev,
				"device %d flush cache failed, status=0x%x.\n",
				device_id, cmd->cmd_status);
		}

		mvumi_delete_internal_cmd(mhba, cmd);
	}
	return 0;
}