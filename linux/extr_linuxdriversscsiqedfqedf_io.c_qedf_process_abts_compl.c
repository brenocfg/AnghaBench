#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qedf_ioreq {int /*<<< orphan*/  refcount; int /*<<< orphan*/  abts_done; scalar_t__ return_scsi_cmd_on_abts; scalar_t__ sc_cmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  event; int /*<<< orphan*/  rrq_work; int /*<<< orphan*/  xid; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  cmd_type; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_3__* lport; int /*<<< orphan*/  dpc_wq; } ;
struct TYPE_4__ {int r_ctl; } ;
struct TYPE_5__ {TYPE_1__ abts_info; } ;
struct fcoe_cqe {TYPE_2__ cqe_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  r_a_tov; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
#define  FC_RCTL_BA_ACC 129 
#define  FC_RCTL_BA_RJT 128 
 int /*<<< orphan*/  QEDF_CMD_IN_ABORT ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDF_IOREQ_EV_ABORT_FAILED ; 
 int /*<<< orphan*/  QEDF_IOREQ_EV_ABORT_SUCCESS ; 
 int /*<<< orphan*/  QEDF_LOG_SCSI_TM ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_scsi_done (struct qedf_ctx*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qedf_process_abts_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	uint32_t r_ctl;
	uint16_t xid;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM, "Entered with xid = "
		   "0x%x cmd_type = %d\n", io_req->xid, io_req->cmd_type);

	cancel_delayed_work(&io_req->timeout_work);

	xid = io_req->xid;
	r_ctl = cqe->cqe_info.abts_info.r_ctl;

	switch (r_ctl) {
	case FC_RCTL_BA_ACC:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM,
		    "ABTS response - ACC Send RRQ after R_A_TOV\n");
		io_req->event = QEDF_IOREQ_EV_ABORT_SUCCESS;
		/*
		 * Dont release this cmd yet. It will be relesed
		 * after we get RRQ response
		 */
		kref_get(&io_req->refcount);
		queue_delayed_work(qedf->dpc_wq, &io_req->rrq_work,
		    msecs_to_jiffies(qedf->lport->r_a_tov));
		break;
	/* For error cases let the cleanup return the command */
	case FC_RCTL_BA_RJT:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM,
		   "ABTS response - RJT\n");
		io_req->event = QEDF_IOREQ_EV_ABORT_FAILED;
		break;
	default:
		QEDF_ERR(&(qedf->dbg_ctx), "Unknown ABTS response\n");
		break;
	}

	clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);

	if (io_req->sc_cmd) {
		if (io_req->return_scsi_cmd_on_abts)
			qedf_scsi_done(qedf, io_req, DID_ERROR);
	}

	/* Notify eh_abort handler that ABTS is complete */
	complete(&io_req->abts_done);

	kref_put(&io_req->refcount, qedf_release_cmd);
}