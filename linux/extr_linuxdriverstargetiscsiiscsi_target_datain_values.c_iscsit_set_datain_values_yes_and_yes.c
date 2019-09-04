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
typedef  scalar_t__ u32 ;
struct iscsi_datain_req {scalar_t__ recovery; scalar_t__ next_burst_len; scalar_t__ read_data_done; scalar_t__ data_sn; scalar_t__ runlength; scalar_t__ begrun; void* dr_complete; scalar_t__ generate_recovery_values; } ;
struct iscsi_datain {scalar_t__ length; int flags; scalar_t__ offset; int /*<<< orphan*/  data_sn; } ;
struct iscsi_conn {TYPE_4__* sess; TYPE_2__* conn_ops; } ;
struct TYPE_5__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ next_burst_len; scalar_t__ read_data_done; int /*<<< orphan*/  data_sn; int /*<<< orphan*/  init_task_tag; TYPE_1__ se_cmd; struct iscsi_conn* conn; } ;
struct TYPE_8__ {TYPE_3__* sess_ops; } ;
struct TYPE_7__ {scalar_t__ MaxBurstLength; scalar_t__ ErrorRecoveryLevel; } ;
struct TYPE_6__ {scalar_t__ MaxRecvDataSegmentLength; } ;

/* Variables and functions */
 void* DATAIN_COMPLETE_CONNECTION_RECOVERY ; 
 void* DATAIN_COMPLETE_NORMAL ; 
 void* DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY ; 
 scalar_t__ DATAIN_WITHIN_COMMAND_RECOVERY ; 
 int ISCSI_FLAG_CMD_FINAL ; 
 int ISCSI_FLAG_DATA_ACK ; 
 int ISCSI_FLAG_DATA_STATUS ; 
 scalar_t__ iscsit_create_recovery_datain_values_datasequenceinorder_yes (struct iscsi_cmd*,struct iscsi_datain_req*) ; 
 struct iscsi_datain_req* iscsit_get_datain_req (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iscsi_datain_req *iscsit_set_datain_values_yes_and_yes(
	struct iscsi_cmd *cmd,
	struct iscsi_datain *datain)
{
	u32 next_burst_len, read_data_done, read_data_left;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_datain_req *dr;

	dr = iscsit_get_datain_req(cmd);
	if (!dr)
		return NULL;

	if (dr->recovery && dr->generate_recovery_values) {
		if (iscsit_create_recovery_datain_values_datasequenceinorder_yes(
					cmd, dr) < 0)
			return NULL;

		dr->generate_recovery_values = 0;
	}

	next_burst_len = (!dr->recovery) ?
			cmd->next_burst_len : dr->next_burst_len;
	read_data_done = (!dr->recovery) ?
			cmd->read_data_done : dr->read_data_done;

	read_data_left = (cmd->se_cmd.data_length - read_data_done);
	if (!read_data_left) {
		pr_err("ITT: 0x%08x read_data_left is zero!\n",
				cmd->init_task_tag);
		return NULL;
	}

	if ((read_data_left <= conn->conn_ops->MaxRecvDataSegmentLength) &&
	    (read_data_left <= (conn->sess->sess_ops->MaxBurstLength -
	     next_burst_len))) {
		datain->length = read_data_left;

		datain->flags |= (ISCSI_FLAG_CMD_FINAL | ISCSI_FLAG_DATA_STATUS);
		if (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
			datain->flags |= ISCSI_FLAG_DATA_ACK;
	} else {
		if ((next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) {
			datain->length =
				conn->conn_ops->MaxRecvDataSegmentLength;
			next_burst_len += datain->length;
		} else {
			datain->length = (conn->sess->sess_ops->MaxBurstLength -
					  next_burst_len);
			next_burst_len = 0;

			datain->flags |= ISCSI_FLAG_CMD_FINAL;
			if (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
				datain->flags |= ISCSI_FLAG_DATA_ACK;
		}
	}

	datain->data_sn = (!dr->recovery) ? cmd->data_sn++ : dr->data_sn++;
	datain->offset = read_data_done;

	if (!dr->recovery) {
		cmd->next_burst_len = next_burst_len;
		cmd->read_data_done += datain->length;
	} else {
		dr->next_burst_len = next_burst_len;
		dr->read_data_done += datain->length;
	}

	if (!dr->recovery) {
		if (datain->flags & ISCSI_FLAG_DATA_STATUS)
			dr->dr_complete = DATAIN_COMPLETE_NORMAL;

		return dr;
	}

	if (!dr->runlength) {
		if (datain->flags & ISCSI_FLAG_DATA_STATUS) {
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		}
	} else {
		if ((dr->begrun + dr->runlength) == dr->data_sn) {
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		}
	}

	return dr;
}