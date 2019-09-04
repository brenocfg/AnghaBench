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
struct iscsi_seq {scalar_t__ data_sn; } ;
struct iscsi_data {int /*<<< orphan*/  datasn; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ data_sn; int /*<<< orphan*/  init_task_tag; struct iscsi_seq* seq_ptr; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ErrorRecoveryLevel; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ iscsit_dump_data_payload (struct iscsi_conn*,scalar_t__,int) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int iscsit_dataout_check_datasn(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	u32 data_sn = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * Considering the target has no method of re-requesting DataOUT
	 * by DataSN, if we receieve a greater DataSN than expected we
	 * assume the functions for DataPDUInOrder=[Yes,No] below will
	 * handle it.
	 *
	 * If the DataSN is less than expected, dump the payload.
	 */
	if (conn->sess->sess_ops->DataSequenceInOrder)
		data_sn = cmd->data_sn;
	else {
		struct iscsi_seq *seq = cmd->seq_ptr;
		data_sn = seq->data_sn;
	}

	if (be32_to_cpu(hdr->datasn) > data_sn) {
		pr_err("Command ITT: 0x%08x, received DataSN: 0x%08x"
			" higher than expected 0x%08x.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->datasn), data_sn);
		goto recover;
	} else if (be32_to_cpu(hdr->datasn) < data_sn) {
		pr_err("Command ITT: 0x%08x, received DataSN: 0x%08x"
			" lower than expected 0x%08x, discarding payload.\n",
			cmd->init_task_tag, be32_to_cpu(hdr->datasn), data_sn);
		goto dump;
	}

	return DATAOUT_NORMAL;

recover:
	if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
		pr_err("Unable to perform within-command recovery"
				" while ERL=0.\n");
		return DATAOUT_CANNOT_RECOVER;
	}
dump:
	if (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
		return DATAOUT_CANNOT_RECOVER;

	return DATAOUT_WITHIN_COMMAND_RECOVERY;
}