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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct qedf_rport {int /*<<< orphan*/  rport_lock; struct fcoe_wqe* sq; int /*<<< orphan*/  flags; int /*<<< orphan*/  free_sqes; struct qedf_ctx* qedf; struct fc_rport_priv* rdata; } ;
struct qedf_ioreq {size_t xid; int return_scsi_cmd_on_abts; TYPE_1__* task_params; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cpu; int /*<<< orphan*/  refcount; struct qedf_rport* fcport; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  packet_aborts; int /*<<< orphan*/  control_requests; int /*<<< orphan*/  link_down_tmo_valid; struct fc_lport* lport; } ;
struct fcoe_wqe {int dummy; } ;
struct fc_rport_priv {int /*<<< orphan*/  r_a_tov; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  link_up; } ;
struct TYPE_2__ {struct fcoe_wqe* sqe; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ LPORT_ST_READY ; 
 int QEDF_ABORT_TIMEOUT ; 
 int /*<<< orphan*/  QEDF_ABTS ; 
 int /*<<< orphan*/  QEDF_CMD_IN_ABORT ; 
 int /*<<< orphan*/  QEDF_CMD_IN_CLEANUP ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  QEDF_LOG_SCSI_TM ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  QEDF_RPORT_UPLOADING_CONNECTION ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_initiator_abort_fcoe_task (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fcoe_wqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_cmd_timer_set (struct qedf_ctx*,struct qedf_ioreq*,int) ; 
 size_t qedf_get_sqe_idx (struct qedf_rport*) ; 
 int /*<<< orphan*/  qedf_initiate_cleanup (struct qedf_ioreq*,int) ; 
 int /*<<< orphan*/  qedf_ring_doorbell (struct qedf_rport*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qedf_initiate_abts(struct qedf_ioreq *io_req, bool return_scsi_cmd_on_abts)
{
	struct fc_lport *lport;
	struct qedf_rport *fcport = io_req->fcport;
	struct fc_rport_priv *rdata;
	struct qedf_ctx *qedf;
	u16 xid;
	u32 r_a_tov = 0;
	int rc = 0;
	unsigned long flags;
	struct fcoe_wqe *sqe;
	u16 sqe_idx;

	/* Sanity check qedf_rport before dereferencing any pointers */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(NULL, "tgt not offloaded\n");
		rc = 1;
		goto abts_err;
	}

	rdata = fcport->rdata;
	r_a_tov = rdata->r_a_tov;
	qedf = fcport->qedf;
	lport = qedf->lport;

	if (lport->state != LPORT_ST_READY || !(lport->link_up)) {
		QEDF_ERR(&(qedf->dbg_ctx), "link is not ready\n");
		rc = 1;
		goto abts_err;
	}

	if (atomic_read(&qedf->link_down_tmo_valid) > 0) {
		QEDF_ERR(&(qedf->dbg_ctx), "link_down_tmo active.\n");
		rc = 1;
		goto abts_err;
	}

	/* Ensure room on SQ */
	if (!atomic_read(&fcport->free_sqes)) {
		QEDF_ERR(&(qedf->dbg_ctx), "No SQ entries available\n");
		rc = 1;
		goto abts_err;
	}

	if (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) {
		QEDF_ERR(&qedf->dbg_ctx, "fcport is uploading.\n");
		rc = 1;
		goto out;
	}

	if (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_ABORT, &io_req->flags)) {
		QEDF_ERR(&(qedf->dbg_ctx), "io_req xid=0x%x already in "
			  "cleanup or abort processing or already "
			  "completed.\n", io_req->xid);
		rc = 1;
		goto out;
	}

	kref_get(&io_req->refcount);

	xid = io_req->xid;
	qedf->control_requests++;
	qedf->packet_aborts++;

	/* Set the return CPU to be the same as the request one */
	io_req->cpu = smp_processor_id();

	/* Set the command type to abort */
	io_req->cmd_type = QEDF_ABTS;
	io_req->return_scsi_cmd_on_abts = return_scsi_cmd_on_abts;

	set_bit(QEDF_CMD_IN_ABORT, &io_req->flags);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_SCSI_TM, "ABTS io_req xid = "
		   "0x%x\n", xid);

	qedf_cmd_timer_set(qedf, io_req, QEDF_ABORT_TIMEOUT * HZ);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	memset(sqe, 0, sizeof(struct fcoe_wqe));
	io_req->task_params->sqe = sqe;

	init_initiator_abort_fcoe_task(io_req->task_params);
	qedf_ring_doorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);

	return rc;
abts_err:
	/*
	 * If the ABTS task fails to queue then we need to cleanup the
	 * task at the firmware.
	 */
	qedf_initiate_cleanup(io_req, return_scsi_cmd_on_abts);
out:
	return rc;
}