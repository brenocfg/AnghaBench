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
struct iscsi_seq {size_t pdu_start; int pdu_count; } ;
struct iscsi_pdu {scalar_t__ seq_no; int length; scalar_t__ status; int offset; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {int pdu_count; struct iscsi_pdu* pdu_list; struct iscsi_seq* seq_ptr; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 scalar_t__ ISCSI_PDU_NOT_RECEIVED ; 
 scalar_t__ ISCSI_PDU_RECEIVED_OK ; 
 scalar_t__ iscsit_send_recovery_r2t (struct iscsi_cmd*,int,int) ; 

int iscsit_dataout_datapduinorder_no_fbit(
	struct iscsi_cmd *cmd,
	struct iscsi_pdu *pdu)
{
	int i, send_recovery_r2t = 0, recovery = 0;
	u32 length = 0, offset = 0, pdu_count = 0, xfer_len = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *first_pdu = NULL;

	/*
	 * Get an struct iscsi_pdu pointer to the first PDU, and total PDU count
	 * of the DataOUT sequence.
	 */
	if (conn->sess->sess_ops->DataSequenceInOrder) {
		for (i = 0; i < cmd->pdu_count; i++) {
			if (cmd->pdu_list[i].seq_no == pdu->seq_no) {
				if (!first_pdu)
					first_pdu = &cmd->pdu_list[i];
				xfer_len += cmd->pdu_list[i].length;
				pdu_count++;
			} else if (pdu_count)
				break;
		}
	} else {
		struct iscsi_seq *seq = cmd->seq_ptr;

		first_pdu = &cmd->pdu_list[seq->pdu_start];
		pdu_count = seq->pdu_count;
	}

	if (!first_pdu || !pdu_count)
		return DATAOUT_CANNOT_RECOVER;

	/*
	 * Loop through the ending DataOUT Sequence checking each struct iscsi_pdu.
	 * The following ugly logic does batching of not received PDUs.
	 */
	for (i = 0; i < pdu_count; i++) {
		if (first_pdu[i].status == ISCSI_PDU_RECEIVED_OK) {
			if (!send_recovery_r2t)
				continue;

			if (iscsit_send_recovery_r2t(cmd, offset, length) < 0)
				return DATAOUT_CANNOT_RECOVER;

			send_recovery_r2t = length = offset = 0;
			continue;
		}
		/*
		 * Set recovery = 1 for any missing, CRC failed, or timed
		 * out PDUs to let the DataOUT logic know that this sequence
		 * has not been completed yet.
		 *
		 * Also, only send a Recovery R2T for ISCSI_PDU_NOT_RECEIVED.
		 * We assume if the PDU either failed CRC or timed out
		 * that a Recovery R2T has already been sent.
		 */
		recovery = 1;

		if (first_pdu[i].status != ISCSI_PDU_NOT_RECEIVED)
			continue;

		if (!offset)
			offset = first_pdu[i].offset;
		length += first_pdu[i].length;

		send_recovery_r2t = 1;
	}

	if (send_recovery_r2t)
		if (iscsit_send_recovery_r2t(cmd, offset, length) < 0)
			return DATAOUT_CANNOT_RECOVER;

	return (!recovery) ? DATAOUT_NORMAL : DATAOUT_WITHIN_COMMAND_RECOVERY;
}