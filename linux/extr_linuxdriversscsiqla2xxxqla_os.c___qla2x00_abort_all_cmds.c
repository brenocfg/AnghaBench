#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct req_que {int num_outstanding_cmds; TYPE_4__** outstanding_cmds; } ;
struct qla_tgt_cmd {int /*<<< orphan*/  vha; } ;
struct qla_tgt {int dummy; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; struct req_que* req; TYPE_5__* vha; } ;
struct TYPE_14__ {int /*<<< orphan*/  tgt_ops; } ;
struct TYPE_13__ {int /*<<< orphan*/  eeh_busy; } ;
struct qla_hw_data {TYPE_3__ tgt; TYPE_2__ flags; int /*<<< orphan*/  req_q_map; } ;
struct TYPE_15__ {scalar_t__ cmd_type; scalar_t__ type; int /*<<< orphan*/  (* done ) (TYPE_4__*,int) ;int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_4__ srb_t ;
struct TYPE_12__ {struct qla_tgt* qla_tgt; } ;
struct TYPE_16__ {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; TYPE_1__ vha_tgt; } ;
typedef  TYPE_5__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 int FAILED ; 
 scalar_t__ GET_CMD_SP (TYPE_4__*) ; 
 scalar_t__ SRB_NVME_CMD ; 
 scalar_t__ SRB_NVME_LS ; 
 scalar_t__ SRB_SCSI_CMD ; 
 scalar_t__ TYPE_SRB ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_5__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 scalar_t__ qla2x00_isp_reg_stat (struct qla_hw_data*) ; 
 int qla2xxx_eh_abort (scalar_t__) ; 
 scalar_t__ qla_ini_mode_enabled (TYPE_5__*) ; 
 int /*<<< orphan*/  qla_nvme_abort (struct qla_hw_data*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  qlt_abort_cmd_on_host_reset (int /*<<< orphan*/ ,struct qla_tgt_cmd*) ; 
 int /*<<< orphan*/  sp_get (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__qla2x00_abort_all_cmds(struct qla_qpair *qp, int res)
{
	int cnt, status;
	unsigned long flags;
	srb_t *sp;
	scsi_qla_host_t *vha = qp->vha;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req;
	struct qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	struct qla_tgt_cmd *cmd;
	uint8_t trace = 0;

	if (!ha->req_q_map)
		return;
	spin_lock_irqsave(qp->qp_lock_ptr, flags);
	req = qp->req;
	for (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) {
		sp = req->outstanding_cmds[cnt];
		if (sp) {
			req->outstanding_cmds[cnt] = NULL;
			if (sp->cmd_type == TYPE_SRB) {
				if (sp->type == SRB_NVME_CMD ||
				    sp->type == SRB_NVME_LS) {
					sp_get(sp);
					spin_unlock_irqrestore(qp->qp_lock_ptr,
					    flags);
					qla_nvme_abort(ha, sp, res);
					spin_lock_irqsave(qp->qp_lock_ptr,
					    flags);
				} else if (GET_CMD_SP(sp) &&
				    !ha->flags.eeh_busy &&
				    (!test_bit(ABORT_ISP_ACTIVE,
					&vha->dpc_flags)) &&
				    (sp->type == SRB_SCSI_CMD)) {
					/*
					 * Don't abort commands in
					 * adapter during EEH
					 * recovery as it's not
					 * accessible/responding.
					 *
					 * Get a reference to the sp
					 * and drop the lock. The
					 * reference ensures this
					 * sp->done() call and not the
					 * call in qla2xxx_eh_abort()
					 * ends the SCSI command (with
					 * result 'res').
					 */
					sp_get(sp);
					spin_unlock_irqrestore(qp->qp_lock_ptr,
					    flags);
					status = qla2xxx_eh_abort(
					    GET_CMD_SP(sp));
					spin_lock_irqsave(qp->qp_lock_ptr,
					    flags);
					/*
					 * Get rid of extra reference
					 * if immediate exit from
					 * ql2xxx_eh_abort
					 */
					if (status == FAILED &&
					    (qla2x00_isp_reg_stat(ha)))
						atomic_dec(
						    &sp->ref_count);
				}
				sp->done(sp, res);
			} else {
				if (!vha->hw->tgt.tgt_ops || !tgt ||
				    qla_ini_mode_enabled(vha)) {
					if (!trace)
						ql_dbg(ql_dbg_tgt_mgt,
						    vha, 0xf003,
						    "HOST-ABORT-HNDLR: dpc_flags=%lx. Target mode disabled\n",
						    vha->dpc_flags);
					continue;
				}
				cmd = (struct qla_tgt_cmd *)sp;
				qlt_abort_cmd_on_host_reset(cmd->vha, cmd);
			}
		}
	}
	spin_unlock_irqrestore(qp->qp_lock_ptr, flags);
}