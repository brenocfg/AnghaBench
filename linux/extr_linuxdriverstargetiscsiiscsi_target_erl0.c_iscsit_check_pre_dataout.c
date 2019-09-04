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
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ unsolicited_data; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ DataPDUInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 int iscsit_dataout_check_datasn (struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_dataout_check_sequence (struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_dataout_check_unsolicited_sequence (struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_dataout_pre_datapduinorder_no (struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_dataout_pre_datapduinorder_yes (struct iscsi_cmd*,unsigned char*) ; 
 int iscsit_dataout_within_command_recovery_check (struct iscsi_cmd*,unsigned char*) ; 

int iscsit_check_pre_dataout(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	int ret;
	struct iscsi_conn *conn = cmd->conn;

	ret = iscsit_dataout_within_command_recovery_check(cmd, buf);
	if ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
	    (ret == DATAOUT_CANNOT_RECOVER))
		return ret;

	ret = iscsit_dataout_check_datasn(cmd, buf);
	if ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
	    (ret == DATAOUT_CANNOT_RECOVER))
		return ret;

	if (cmd->unsolicited_data) {
		ret = iscsit_dataout_check_unsolicited_sequence(cmd, buf);
		if ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
		    (ret == DATAOUT_CANNOT_RECOVER))
			return ret;
	} else {
		ret = iscsit_dataout_check_sequence(cmd, buf);
		if ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
		    (ret == DATAOUT_CANNOT_RECOVER))
			return ret;
	}

	return (conn->sess->sess_ops->DataPDUInOrder) ?
		iscsit_dataout_pre_datapduinorder_yes(cmd, buf) :
		iscsit_dataout_pre_datapduinorder_no(cmd, buf);
}