#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {scalar_t__ data_length; } ;
struct iscsi_task {scalar_t__ imm_count; TYPE_6__* conn; TYPE_1__ unsol_r2t; struct bnx2i_cmd* dd_data; } ;
struct TYPE_11__ {scalar_t__ total_data_transfer_length; scalar_t__ sd_start_bd_index; scalar_t__ sd_buffer_offset; scalar_t__ ud_start_bd_index; scalar_t__ ud_buffer_offset; } ;
struct TYPE_10__ {int bd_valid; TYPE_3__* bd_tbl; } ;
struct bnx2i_cmd {TYPE_5__ req; TYPE_4__ io_tbl; int /*<<< orphan*/  scsi_cmd; } ;
struct TYPE_12__ {TYPE_2__* session; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_length; } ;
struct TYPE_8__ {scalar_t__ first_burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ALERT ; 
 int /*<<< orphan*/  bnx2i_get_write_cmd_bd_idx (struct bnx2i_cmd*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,TYPE_6__*,char*,int,int,...) ; 
 scalar_t__ iscsi_task_has_unsol_data (struct iscsi_task*) ; 
 scalar_t__ scsi_sg_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_setup_write_cmd_bd_info(struct iscsi_task *task)
{
	struct bnx2i_cmd *cmd = task->dd_data;
	u32 start_bd_offset;
	u32 start_bd_idx;
	u32 buffer_offset = 0;
	u32 cmd_len = cmd->req.total_data_transfer_length;

	/* if ImmediateData is turned off & IntialR2T is turned on,
	 * there will be no immediate or unsolicited data, just return.
	 */
	if (!iscsi_task_has_unsol_data(task) && !task->imm_count)
		return;

	/* Immediate data */
	buffer_offset += task->imm_count;
	if (task->imm_count == cmd_len)
		return;

	if (iscsi_task_has_unsol_data(task)) {
		bnx2i_get_write_cmd_bd_idx(cmd, buffer_offset,
					   &start_bd_offset, &start_bd_idx);
		cmd->req.ud_buffer_offset = start_bd_offset;
		cmd->req.ud_start_bd_index = start_bd_idx;
		buffer_offset += task->unsol_r2t.data_length;
	}

	if (buffer_offset != cmd_len) {
		bnx2i_get_write_cmd_bd_idx(cmd, buffer_offset,
					   &start_bd_offset, &start_bd_idx);
		if ((start_bd_offset > task->conn->session->first_burst) ||
		    (start_bd_idx > scsi_sg_count(cmd->scsi_cmd))) {
			int i = 0;

			iscsi_conn_printk(KERN_ALERT, task->conn,
					  "bnx2i- error, buf offset 0x%x "
					  "bd_valid %d use_sg %d\n",
					  buffer_offset, cmd->io_tbl.bd_valid,
					  scsi_sg_count(cmd->scsi_cmd));
			for (i = 0; i < cmd->io_tbl.bd_valid; i++)
				iscsi_conn_printk(KERN_ALERT, task->conn,
						  "bnx2i err, bd[%d]: len %x\n",
						  i, cmd->io_tbl.bd_tbl[i].\
						  buffer_length);
		}
		cmd->req.sd_buffer_offset = start_bd_offset;
		cmd->req.sd_start_bd_index = start_bd_idx;
	}
}