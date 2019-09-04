#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {scalar_t__ acked_data_sn; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICF_GOT_DATACK_SNACK ; 
 struct iscsi_cmd* iscsit_find_cmd_from_ttt (struct iscsi_conn*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 

int iscsit_handle_data_ack(
	struct iscsi_conn *conn,
	u32 targ_xfer_tag,
	u32 begrun,
	u32 runlength)
{
	struct iscsi_cmd *cmd = NULL;

	cmd = iscsit_find_cmd_from_ttt(conn, targ_xfer_tag);
	if (!cmd) {
		pr_err("Data ACK SNACK for TTT: 0x%08x is"
			" invalid.\n", targ_xfer_tag);
		return -1;
	}

	if (begrun <= cmd->acked_data_sn) {
		pr_err("ITT: 0x%08x Data ACK SNACK BegRUN: 0x%08x is"
			" less than the already acked DataSN: 0x%08x.\n",
			cmd->init_task_tag, begrun, cmd->acked_data_sn);
		return -1;
	}

	/*
	 * For Data ACK SNACK, BegRun is the next expected DataSN.
	 * (see iSCSI v19: 10.16.6)
	 */
	cmd->cmd_flags |= ICF_GOT_DATACK_SNACK;
	cmd->acked_data_sn = (begrun - 1);

	pr_debug("Received Data ACK SNACK for ITT: 0x%08x,"
		" updated acked DataSN to 0x%08x.\n",
			cmd->init_task_tag, cmd->acked_data_sn);

	return 0;
}