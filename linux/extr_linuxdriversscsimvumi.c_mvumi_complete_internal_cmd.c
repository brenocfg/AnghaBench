#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mvumi_sense_data {int dummy; } ;
struct mvumi_rsp_frame {scalar_t__ req_status; int rsp_flag; int /*<<< orphan*/  payload; } ;
struct mvumi_hba {int /*<<< orphan*/  int_cmd_wait_q; } ;
struct mvumi_cmd {scalar_t__ cmd_status; int /*<<< orphan*/  sync_cmd; scalar_t__ data_buf; } ;

/* Variables and functions */
 int CL_RSP_FLAG_SENSEDATA ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvumi_complete_internal_cmd(struct mvumi_hba *mhba,
						struct mvumi_cmd *cmd,
					struct mvumi_rsp_frame *ob_frame)
{
	if (atomic_read(&cmd->sync_cmd)) {
		cmd->cmd_status = ob_frame->req_status;

		if ((ob_frame->req_status == SAM_STAT_CHECK_CONDITION) &&
				(ob_frame->rsp_flag & CL_RSP_FLAG_SENSEDATA) &&
				cmd->data_buf) {
			memcpy(cmd->data_buf, ob_frame->payload,
					sizeof(struct mvumi_sense_data));
		}
		atomic_dec(&cmd->sync_cmd);
		wake_up(&mhba->int_cmd_wait_q);
	}
}