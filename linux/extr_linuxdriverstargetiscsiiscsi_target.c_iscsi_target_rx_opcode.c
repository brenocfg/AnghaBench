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
struct iscsi_hdr {int opcode; int /*<<< orphan*/  itt; int /*<<< orphan*/  ttt; } ;
struct iscsi_conn {TYPE_2__* sess; int /*<<< orphan*/  conn_logout_comp; } ;
struct iscsi_cmd {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ErrorRecoveryLevel; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_OPCODE_MASK ; 
#define  ISCSI_OP_LOGOUT 134 
#define  ISCSI_OP_NOOP_OUT 133 
#define  ISCSI_OP_SCSI_CMD 132 
#define  ISCSI_OP_SCSI_DATA_OUT 131 
#define  ISCSI_OP_SCSI_TMFUNC 130 
#define  ISCSI_OP_SNACK 129 
#define  ISCSI_OP_TEXT 128 
 int /*<<< orphan*/  ISCSI_REASON_BOOKMARK_NO_RESOURCES ; 
 int SECONDS_FOR_LOGOUT_COMP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int iscsit_add_reject (struct iscsi_conn*,int /*<<< orphan*/ ,unsigned char*) ; 
 struct iscsi_cmd* iscsit_allocate_cmd (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 struct iscsi_cmd* iscsit_find_cmd_from_itt (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_handle_data_out (struct iscsi_conn*,unsigned char*) ; 
 int iscsit_handle_logout_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_handle_nop_out (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_handle_scsi_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_handle_snack (struct iscsi_conn*,unsigned char*) ; 
 int iscsit_handle_task_mgt_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_handle_text_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int iscsi_target_rx_opcode(struct iscsi_conn *conn, unsigned char *buf)
{
	struct iscsi_hdr *hdr = (struct iscsi_hdr *)buf;
	struct iscsi_cmd *cmd;
	int ret = 0;

	switch (hdr->opcode & ISCSI_OPCODE_MASK) {
	case ISCSI_OP_SCSI_CMD:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		if (!cmd)
			goto reject;

		ret = iscsit_handle_scsi_cmd(conn, cmd, buf);
		break;
	case ISCSI_OP_SCSI_DATA_OUT:
		ret = iscsit_handle_data_out(conn, buf);
		break;
	case ISCSI_OP_NOOP_OUT:
		cmd = NULL;
		if (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) {
			cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
			if (!cmd)
				goto reject;
		}
		ret = iscsit_handle_nop_out(conn, cmd, buf);
		break;
	case ISCSI_OP_SCSI_TMFUNC:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		if (!cmd)
			goto reject;

		ret = iscsit_handle_task_mgt_cmd(conn, cmd, buf);
		break;
	case ISCSI_OP_TEXT:
		if (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) {
			cmd = iscsit_find_cmd_from_itt(conn, hdr->itt);
			if (!cmd)
				goto reject;
		} else {
			cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
			if (!cmd)
				goto reject;
		}

		ret = iscsit_handle_text_cmd(conn, cmd, buf);
		break;
	case ISCSI_OP_LOGOUT:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		if (!cmd)
			goto reject;

		ret = iscsit_handle_logout_cmd(conn, cmd, buf);
		if (ret > 0)
			wait_for_completion_timeout(&conn->conn_logout_comp,
					SECONDS_FOR_LOGOUT_COMP * HZ);
		break;
	case ISCSI_OP_SNACK:
		ret = iscsit_handle_snack(conn, buf);
		break;
	default:
		pr_err("Got unknown iSCSI OpCode: 0x%02x\n", hdr->opcode);
		if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
			pr_err("Cannot recover from unknown"
			" opcode while ERL=0, closing iSCSI connection.\n");
			return -1;
		}
		pr_err("Unable to recover from unknown opcode while OFMarker=No,"
		       " closing iSCSI connection.\n");
		ret = -1;
		break;
	}

	return ret;
reject:
	return iscsit_add_reject(conn, ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
}