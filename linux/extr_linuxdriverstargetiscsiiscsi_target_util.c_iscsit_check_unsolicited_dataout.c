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
struct se_cmd {scalar_t__ data_length; } ;
struct iscsi_data {int flags; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ first_burst_len; struct se_cmd se_cmd; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ FirstBurstLength; scalar_t__ InitialR2T; } ;

/* Variables and functions */
 int ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  TCM_INCORRECT_AMOUNT_OF_DATA ; 
 int /*<<< orphan*/  TCM_UNEXPECTED_UNSOLICITED_DATA ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  transport_send_check_condition_and_sense (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iscsit_check_unsolicited_dataout(struct iscsi_cmd *cmd, unsigned char *buf)
{
	struct iscsi_conn *conn = cmd->conn;
	struct se_cmd *se_cmd = &cmd->se_cmd;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	if (conn->sess->sess_ops->InitialR2T) {
		pr_err("Received unexpected unsolicited data"
			" while InitialR2T=Yes, protocol error.\n");
		transport_send_check_condition_and_sense(se_cmd,
				TCM_UNEXPECTED_UNSOLICITED_DATA, 0);
		return -1;
	}

	if ((cmd->first_burst_len + payload_length) >
	     conn->sess->sess_ops->FirstBurstLength) {
		pr_err("Total %u bytes exceeds FirstBurstLength: %u"
			" for this Unsolicited DataOut Burst.\n",
			(cmd->first_burst_len + payload_length),
				conn->sess->sess_ops->FirstBurstLength);
		transport_send_check_condition_and_sense(se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		return -1;
	}

	if (!(hdr->flags & ISCSI_FLAG_CMD_FINAL))
		return 0;

	if (((cmd->first_burst_len + payload_length) != cmd->se_cmd.data_length) &&
	    ((cmd->first_burst_len + payload_length) !=
	      conn->sess->sess_ops->FirstBurstLength)) {
		pr_err("Unsolicited non-immediate data received %u"
			" does not equal FirstBurstLength: %u, and does"
			" not equal ExpXferLen %u.\n",
			(cmd->first_burst_len + payload_length),
			conn->sess->sess_ops->FirstBurstLength, cmd->se_cmd.data_length);
		transport_send_check_condition_and_sense(se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		return -1;
	}
	return 0;
}