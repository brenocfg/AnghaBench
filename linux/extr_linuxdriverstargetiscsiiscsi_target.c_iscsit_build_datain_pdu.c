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
typedef  int u32 ;
struct scsi_lun {int dummy; } ;
struct iscsi_datain {int flags; int data_sn; int offset; int /*<<< orphan*/  length; } ;
struct iscsi_data_rsp {int flags; void* offset; void* datasn; void* statsn; void* max_cmdsn; void* exp_cmdsn; void* ttt; int /*<<< orphan*/  itt; int /*<<< orphan*/  lun; int /*<<< orphan*/  dlength; void* residual_count; int /*<<< orphan*/  opcode; } ;
struct iscsi_conn {int /*<<< orphan*/  cid; TYPE_2__* sess; } ;
struct TYPE_3__ {int se_cmd_flags; int residual_count; int /*<<< orphan*/  orig_fe_lun; } ;
struct iscsi_cmd {int targ_xfer_tag; int stat_sn; int /*<<< orphan*/  init_task_tag; TYPE_1__ se_cmd; } ;
struct TYPE_4__ {int exp_cmd_sn; int /*<<< orphan*/  max_cmd_sn; } ;

/* Variables and functions */
 int ISCSI_FLAG_DATA_ACK ; 
 int ISCSI_FLAG_DATA_OVERFLOW ; 
 int ISCSI_FLAG_DATA_STATUS ; 
 int ISCSI_FLAG_DATA_UNDERFLOW ; 
 int /*<<< orphan*/  ISCSI_OP_SCSI_DATA_IN ; 
 int SCF_OVERFLOW_BIT ; 
 int SCF_UNDERFLOW_BIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  ntohl (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int,int /*<<< orphan*/ *) ; 

void
iscsit_build_datain_pdu(struct iscsi_cmd *cmd, struct iscsi_conn *conn,
			struct iscsi_datain *datain, struct iscsi_data_rsp *hdr,
			bool set_statsn)
{
	hdr->opcode		= ISCSI_OP_SCSI_DATA_IN;
	hdr->flags		= datain->flags;
	if (hdr->flags & ISCSI_FLAG_DATA_STATUS) {
		if (cmd->se_cmd.se_cmd_flags & SCF_OVERFLOW_BIT) {
			hdr->flags |= ISCSI_FLAG_DATA_OVERFLOW;
			hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
		} else if (cmd->se_cmd.se_cmd_flags & SCF_UNDERFLOW_BIT) {
			hdr->flags |= ISCSI_FLAG_DATA_UNDERFLOW;
			hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
		}
	}
	hton24(hdr->dlength, datain->length);
	if (hdr->flags & ISCSI_FLAG_DATA_ACK)
		int_to_scsilun(cmd->se_cmd.orig_fe_lun,
				(struct scsi_lun *)&hdr->lun);
	else
		put_unaligned_le64(0xFFFFFFFFFFFFFFFFULL, &hdr->lun);

	hdr->itt		= cmd->init_task_tag;

	if (hdr->flags & ISCSI_FLAG_DATA_ACK)
		hdr->ttt		= cpu_to_be32(cmd->targ_xfer_tag);
	else
		hdr->ttt		= cpu_to_be32(0xFFFFFFFF);
	if (set_statsn)
		hdr->statsn		= cpu_to_be32(cmd->stat_sn);
	else
		hdr->statsn		= cpu_to_be32(0xFFFFFFFF);

	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));
	hdr->datasn		= cpu_to_be32(datain->data_sn);
	hdr->offset		= cpu_to_be32(datain->offset);

	pr_debug("Built DataIN ITT: 0x%08x, StatSN: 0x%08x,"
		" DataSN: 0x%08x, Offset: %u, Length: %u, CID: %hu\n",
		cmd->init_task_tag, ntohl(hdr->statsn), ntohl(hdr->datasn),
		ntohl(hdr->offset), datain->length, conn->cid);
}