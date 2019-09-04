#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iscsi_scsi_rsp {void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  itt; int /*<<< orphan*/  cmd_status; int /*<<< orphan*/  response; void* residual_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_conn {int /*<<< orphan*/  cid; TYPE_2__* sess; int /*<<< orphan*/  stat_sn; } ;
struct TYPE_3__ {int se_cmd_flags; int /*<<< orphan*/  scsi_status; scalar_t__ residual_count; } ;
struct iscsi_cmd {TYPE_1__ se_cmd; scalar_t__ stat_sn; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  iscsi_response; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_cmd_sn; scalar_t__ exp_cmd_sn; int /*<<< orphan*/  rsp_pdus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  ISCSI_FLAG_CMD_OVERFLOW ; 
 int /*<<< orphan*/  ISCSI_FLAG_CMD_UNDERFLOW ; 
 int /*<<< orphan*/  ISCSI_HDR_LEN ; 
 int /*<<< orphan*/  ISCSI_OP_SCSI_CMD_RSP ; 
 int SCF_OVERFLOW_BIT ; 
 int SCF_UNDERFLOW_BIT ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  iscsit_increment_maxcmdsn (struct iscsi_cmd*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct iscsi_scsi_rsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iscsit_build_rsp_pdu(struct iscsi_cmd *cmd, struct iscsi_conn *conn,
			bool inc_stat_sn, struct iscsi_scsi_rsp *hdr)
{
	if (inc_stat_sn)
		cmd->stat_sn = conn->stat_sn++;

	atomic_long_inc(&conn->sess->rsp_pdus);

	memset(hdr, 0, ISCSI_HDR_LEN);
	hdr->opcode		= ISCSI_OP_SCSI_CMD_RSP;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	if (cmd->se_cmd.se_cmd_flags & SCF_OVERFLOW_BIT) {
		hdr->flags |= ISCSI_FLAG_CMD_OVERFLOW;
		hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
	} else if (cmd->se_cmd.se_cmd_flags & SCF_UNDERFLOW_BIT) {
		hdr->flags |= ISCSI_FLAG_CMD_UNDERFLOW;
		hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
	}
	hdr->response		= cmd->iscsi_response;
	hdr->cmd_status		= cmd->se_cmd.scsi_status;
	hdr->itt		= cmd->init_task_tag;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));

	pr_debug("Built SCSI Response, ITT: 0x%08x, StatSN: 0x%08x,"
		" Response: 0x%02x, SAM Status: 0x%02x, CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, cmd->se_cmd.scsi_status,
		cmd->se_cmd.scsi_status, conn->cid);
}