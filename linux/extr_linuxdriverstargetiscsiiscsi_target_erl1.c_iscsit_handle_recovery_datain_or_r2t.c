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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int data_direction; } ;
typedef  int /*<<< orphan*/  itt_t ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 struct iscsi_cmd* iscsit_find_cmd_from_itt (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_handle_r2t_snack (struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsit_handle_recovery_datain (struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int iscsit_handle_recovery_datain_or_r2t(
	struct iscsi_conn *conn,
	unsigned char *buf,
	itt_t init_task_tag,
	u32 targ_xfer_tag,
	u32 begrun,
	u32 runlength)
{
	struct iscsi_cmd *cmd;

	cmd = iscsit_find_cmd_from_itt(conn, init_task_tag);
	if (!cmd)
		return 0;

	/*
	 * FIXME: This will not work for bidi commands.
	 */
	switch (cmd->data_direction) {
	case DMA_TO_DEVICE:
		return iscsit_handle_r2t_snack(cmd, buf, begrun, runlength);
	case DMA_FROM_DEVICE:
		return iscsit_handle_recovery_datain(cmd, buf, begrun,
				runlength);
	default:
		pr_err("Unknown cmd->data_direction: 0x%02x\n",
				cmd->data_direction);
		return -1;
	}

	return 0;
}