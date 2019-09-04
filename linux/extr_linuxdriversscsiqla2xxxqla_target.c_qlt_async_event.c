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
typedef  int uint16_t ;
struct TYPE_2__ {struct qla_tgt* qla_tgt; } ;
struct scsi_qla_host {struct qla_hw_data* hw; int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  dpc_flags; TYPE_1__ vha_tgt; } ;
struct qla_tgt {int /*<<< orphan*/  link_reinit_iocb_pending; int /*<<< orphan*/  link_reinit_iocb; scalar_t__ tgt_stopped; scalar_t__ tgt_stop; } ;
struct qla_hw_data {int exch_starvation; int /*<<< orphan*/  base_qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_CTX_RESET_NEEDED ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  IS_P3P_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 int MBA_CHG_IN_CONNECTION ; 
#define  MBA_LIP_OCCURRED 139 
#define  MBA_LIP_RESET 138 
#define  MBA_LOOP_DOWN 137 
#define  MBA_LOOP_UP 136 
 int MBA_POINT_TO_POINT ; 
#define  MBA_PORT_UPDATE 135 
#define  MBA_REJECTED_FCP_CMD 134 
#define  MBA_REQ_TRANSFER_ERR 133 
#define  MBA_RESET 132 
#define  MBA_RSCN_UPDATE 131 
#define  MBA_RSP_TRANSFER_ERR 130 
#define  MBA_SYSTEM_ERR 129 
#define  MBA_WAKEUP_THRES 128 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qlt_send_notify_ack (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlt_async_event(uint16_t code, struct scsi_qla_host *vha,
	uint16_t *mailbox)
{
	struct qla_hw_data *ha = vha->hw;
	struct qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	int login_code;

	if (!tgt || tgt->tgt_stop || tgt->tgt_stopped)
		return;

	if (((code == MBA_POINT_TO_POINT) || (code == MBA_CHG_IN_CONNECTION)) &&
	    IS_QLA2100(ha))
		return;
	/*
	 * In tgt_stop mode we also should allow all requests to pass.
	 * Otherwise, some commands can stuck.
	 */


	switch (code) {
	case MBA_RESET:			/* Reset */
	case MBA_SYSTEM_ERR:		/* System Error */
	case MBA_REQ_TRANSFER_ERR:	/* Request Transfer Error */
	case MBA_RSP_TRANSFER_ERR:	/* Response Transfer Error */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03a,
		    "qla_target(%d): System error async event %#x "
		    "occurred", vha->vp_idx, code);
		break;
	case MBA_WAKEUP_THRES:		/* Request Queue Wake-up. */
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		break;

	case MBA_LOOP_UP:
	{
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03b,
		    "qla_target(%d): Async LOOP_UP occurred "
		    "(m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)", vha->vp_idx,
		    le16_to_cpu(mailbox[0]), le16_to_cpu(mailbox[1]),
		    le16_to_cpu(mailbox[2]), le16_to_cpu(mailbox[3]));
		if (tgt->link_reinit_iocb_pending) {
			qlt_send_notify_ack(ha->base_qpair,
			    (void *)&tgt->link_reinit_iocb,
			    0, 0, 0, 0, 0, 0);
			tgt->link_reinit_iocb_pending = 0;
		}
		break;
	}

	case MBA_LIP_OCCURRED:
	case MBA_LOOP_DOWN:
	case MBA_LIP_RESET:
	case MBA_RSCN_UPDATE:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03c,
		    "qla_target(%d): Async event %#x occurred "
		    "(m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)", vha->vp_idx, code,
		    le16_to_cpu(mailbox[0]), le16_to_cpu(mailbox[1]),
		    le16_to_cpu(mailbox[2]), le16_to_cpu(mailbox[3]));
		break;

	case MBA_REJECTED_FCP_CMD:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf017,
		    "qla_target(%d): Async event LS_REJECT occurred (m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)",
		    vha->vp_idx,
		    le16_to_cpu(mailbox[0]), le16_to_cpu(mailbox[1]),
		    le16_to_cpu(mailbox[2]), le16_to_cpu(mailbox[3]));

		if (le16_to_cpu(mailbox[3]) == 1) {
			/* exchange starvation. */
			vha->hw->exch_starvation++;
			if (vha->hw->exch_starvation > 5) {
				ql_log(ql_log_warn, vha, 0xd03a,
				    "Exchange starvation-. Resetting RISC\n");

				vha->hw->exch_starvation = 0;
				if (IS_P3P_TYPE(vha->hw))
					set_bit(FCOE_CTX_RESET_NEEDED,
					    &vha->dpc_flags);
				else
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			}
		}
		break;

	case MBA_PORT_UPDATE:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03d,
		    "qla_target(%d): Port update async event %#x "
		    "occurred: updating the ports database (m[0]=%x, m[1]=%x, "
		    "m[2]=%x, m[3]=%x)", vha->vp_idx, code,
		    le16_to_cpu(mailbox[0]), le16_to_cpu(mailbox[1]),
		    le16_to_cpu(mailbox[2]), le16_to_cpu(mailbox[3]));

		login_code = le16_to_cpu(mailbox[2]);
		if (login_code == 0x4) {
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03e,
			    "Async MB 2: Got PLOGI Complete\n");
			vha->hw->exch_starvation = 0;
		} else if (login_code == 0x7)
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03f,
			    "Async MB 2: Port Logged Out\n");
		break;
	default:
		break;
	}

}