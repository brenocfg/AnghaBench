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
struct iscsi_seq {scalar_t__ orig_offset; scalar_t__ xfer_len; scalar_t__ offset; int pdu_count; int pdu_start; int /*<<< orphan*/  status; scalar_t__ next_burst_len; scalar_t__ data_sn; } ;
struct iscsi_pdu {scalar_t__ status; scalar_t__ offset; scalar_t__ length; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ write_data_done; scalar_t__ seq_end_offset; scalar_t__ seq_start_offset; int pdu_count; scalar_t__ first_burst_len; struct iscsi_pdu* pdu_list; scalar_t__ immediate_data; int /*<<< orphan*/  next_burst_len; int /*<<< orphan*/  unsolicited_data; scalar_t__ data_sn; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ DataPDUInOrder; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY ; 
 void* ISCSI_PDU_NOT_RECEIVED ; 
 scalar_t__ ISCSI_PDU_RECEIVED_OK ; 
 struct iscsi_seq* iscsit_get_seq_holder (struct iscsi_cmd*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int iscsit_recalculate_dataout_values(
	struct iscsi_cmd *cmd,
	u32 pdu_offset,
	u32 pdu_length,
	u32 *r2t_offset,
	u32 *r2t_length)
{
	int i;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *pdu = NULL;

	if (conn->sess->sess_ops->DataSequenceInOrder) {
		cmd->data_sn = 0;

		if (conn->sess->sess_ops->DataPDUInOrder) {
			*r2t_offset = cmd->write_data_done;
			*r2t_length = (cmd->seq_end_offset -
					cmd->write_data_done);
			return 0;
		}

		*r2t_offset = cmd->seq_start_offset;
		*r2t_length = (cmd->seq_end_offset - cmd->seq_start_offset);

		for (i = 0; i < cmd->pdu_count; i++) {
			pdu = &cmd->pdu_list[i];

			if (pdu->status != ISCSI_PDU_RECEIVED_OK)
				continue;

			if ((pdu->offset >= cmd->seq_start_offset) &&
			   ((pdu->offset + pdu->length) <=
			     cmd->seq_end_offset)) {
				if (!cmd->unsolicited_data)
					cmd->next_burst_len -= pdu->length;
				else
					cmd->first_burst_len -= pdu->length;

				cmd->write_data_done -= pdu->length;
				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			}
		}
	} else {
		struct iscsi_seq *seq = NULL;

		seq = iscsit_get_seq_holder(cmd, pdu_offset, pdu_length);
		if (!seq)
			return -1;

		*r2t_offset = seq->orig_offset;
		*r2t_length = seq->xfer_len;

		cmd->write_data_done -= (seq->offset - seq->orig_offset);
		if (cmd->immediate_data)
			cmd->first_burst_len = cmd->write_data_done;

		seq->data_sn = 0;
		seq->offset = seq->orig_offset;
		seq->next_burst_len = 0;
		seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY;

		if (conn->sess->sess_ops->DataPDUInOrder)
			return 0;

		for (i = 0; i < seq->pdu_count; i++) {
			pdu = &cmd->pdu_list[i+seq->pdu_start];

			if (pdu->status != ISCSI_PDU_RECEIVED_OK)
				continue;

			pdu->status = ISCSI_PDU_NOT_RECEIVED;
		}
	}

	return 0;
}