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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_tgt_cmd {scalar_t__ state; int /*<<< orphan*/  trc_flags; scalar_t__ write_data_transferred; scalar_t__ sg_mapped; } ;
struct TYPE_4__ {TYPE_1__* tgt_ops; } ;
struct qla_hw_data {TYPE_2__ tgt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_cmd ) (struct qla_tgt_cmd*) ;int /*<<< orphan*/  (* handle_data ) (struct qla_tgt_cmd*) ;} ;

/* Variables and functions */
 scalar_t__ QLA_TGT_STATE_DATA_IN ; 
 scalar_t__ QLA_TGT_STATE_NEED_DATA ; 
 scalar_t__ QLA_TGT_STATE_PROCESSED ; 
 int /*<<< orphan*/  TRC_FLUSH ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  qlt_unmap_sg (struct scsi_qla_host*,struct qla_tgt_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct qla_tgt_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct qla_tgt_cmd*) ; 

void
qlt_abort_cmd_on_host_reset(struct scsi_qla_host *vha, struct qla_tgt_cmd *cmd)
{
	struct qla_hw_data *ha = vha->hw;

	if (cmd->sg_mapped)
		qlt_unmap_sg(vha, cmd);

	/* TODO: fix debug message type and ids. */
	if (cmd->state == QLA_TGT_STATE_PROCESSED) {
		ql_dbg(ql_dbg_io, vha, 0xff00,
		    "HOST-ABORT: state=PROCESSED.\n");
	} else if (cmd->state == QLA_TGT_STATE_NEED_DATA) {
		cmd->write_data_transferred = 0;
		cmd->state = QLA_TGT_STATE_DATA_IN;

		ql_dbg(ql_dbg_io, vha, 0xff01,
		    "HOST-ABORT: state=DATA_IN.\n");

		ha->tgt.tgt_ops->handle_data(cmd);
		return;
	} else {
		ql_dbg(ql_dbg_io, vha, 0xff03,
		    "HOST-ABORT: state=BAD(%d).\n",
		    cmd->state);
		dump_stack();
	}

	cmd->trc_flags |= TRC_FLUSH;
	ha->tgt.tgt_ops->free_cmd(cmd);
}