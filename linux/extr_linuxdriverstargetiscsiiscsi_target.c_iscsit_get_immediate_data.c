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
struct iscsi_scsi_req {int /*<<< orphan*/  cmdsn; } ;
struct TYPE_2__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ first_burst_len; int /*<<< orphan*/  i_state; int /*<<< orphan*/  conn; scalar_t__ unsolicited_data; TYPE_1__ se_cmd; scalar_t__ sense_reason; } ;

/* Variables and functions */
 int CMDSN_ERROR_CANNOT_RECOVER ; 
 int CMDSN_LOWER_THAN_EXP ; 
 int IMMEDIATE_DATA_ERL1_CRC_FAILURE ; 
 int IMMEDIATE_DATA_NORMAL_OPERATION ; 
 int /*<<< orphan*/  ISTATE_REMOVE ; 
 scalar_t__ TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsit_dump_data_payload (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int iscsit_handle_immediate_data (struct iscsi_cmd*,struct iscsi_scsi_req*,scalar_t__) ; 
 int iscsit_sequence_cmd (int /*<<< orphan*/ ,struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_set_unsoliticed_dataout (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  target_put_sess_cmd (TYPE_1__*) ; 

__attribute__((used)) static int
iscsit_get_immediate_data(struct iscsi_cmd *cmd, struct iscsi_scsi_req *hdr,
			  bool dump_payload)
{
	int cmdsn_ret = 0, immed_ret = IMMEDIATE_DATA_NORMAL_OPERATION;
	/*
	 * Special case for Unsupported SAM WRITE Opcodes and ImmediateData=Yes.
	 */
	if (dump_payload)
		goto after_immediate_data;
	/*
	 * Check for underflow case where both EDTL and immediate data payload
	 * exceeds what is presented by CDB's TRANSFER LENGTH, and what has
	 * already been set in target_cmd_size_check() as se_cmd->data_length.
	 *
	 * For this special case, fail the command and dump the immediate data
	 * payload.
	 */
	if (cmd->first_burst_len > cmd->se_cmd.data_length) {
		cmd->sense_reason = TCM_INVALID_CDB_FIELD;
		goto after_immediate_data;
	}

	immed_ret = iscsit_handle_immediate_data(cmd, hdr,
					cmd->first_burst_len);
after_immediate_data:
	if (immed_ret == IMMEDIATE_DATA_NORMAL_OPERATION) {
		/*
		 * A PDU/CmdSN carrying Immediate Data passed
		 * DataCRC, check against ExpCmdSN/MaxCmdSN if
		 * Immediate Bit is not set.
		 */
		cmdsn_ret = iscsit_sequence_cmd(cmd->conn, cmd,
					(unsigned char *)hdr, hdr->cmdsn);
		if (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			return -1;

		if (cmd->sense_reason || cmdsn_ret == CMDSN_LOWER_THAN_EXP) {
			int rc;

			rc = iscsit_dump_data_payload(cmd->conn,
						      cmd->first_burst_len, 1);
			target_put_sess_cmd(&cmd->se_cmd);
			return rc;
		} else if (cmd->unsolicited_data)
			iscsit_set_unsoliticed_dataout(cmd);

	} else if (immed_ret == IMMEDIATE_DATA_ERL1_CRC_FAILURE) {
		/*
		 * Immediate Data failed DataCRC and ERL>=1,
		 * silently drop this PDU and let the initiator
		 * plug the CmdSN gap.
		 *
		 * FIXME: Send Unsolicited NOPIN with reserved
		 * TTT here to help the initiator figure out
		 * the missing CmdSN, although they should be
		 * intelligent enough to determine the missing
		 * CmdSN and issue a retry to plug the sequence.
		 */
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, cmd->i_state);
	} else /* immed_ret == IMMEDIATE_DATA_CANNOT_RECOVER */
		return -1;

	return 0;
}