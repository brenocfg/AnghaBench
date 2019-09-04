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
struct TYPE_3__ {scalar_t__ ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; TYPE_2__* device; } ;
struct qedf_rport {int dummy; } ;
struct qedf_ioreq {scalar_t__ event; int /*<<< orphan*/  xid; int /*<<< orphan*/  abts_done; int /*<<< orphan*/  fp_idx; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; scalar_t__ stop_io_on_error; } ;
struct fc_rport_libfc_priv {int dummy; } ;
struct fc_rport {struct fc_rport_libfc_priv* dd_data; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  link_up; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ QEDF_IOREQ_EV_ABORT_FAILED ; 
 scalar_t__ QEDF_IOREQ_EV_ABORT_SUCCESS ; 
 scalar_t__ QEDF_IOREQ_EV_CLEANUP_SUCCESS ; 
 int SUCCESS ; 
 scalar_t__ fc_remote_port_chkready (struct fc_rport*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ lport_priv (struct fc_lport*) ; 
 int qedf_initiate_abts (struct qedf_ioreq*,int) ; 
 int /*<<< orphan*/  qedf_stop_all_io (struct qedf_ctx*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_2__*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_eh_abort(struct scsi_cmnd *sc_cmd)
{
	struct fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	struct fc_rport_libfc_priv *rp = rport->dd_data;
	struct qedf_rport *fcport;
	struct fc_lport *lport;
	struct qedf_ctx *qedf;
	struct qedf_ioreq *io_req;
	int rc = FAILED;
	int rval;

	if (fc_remote_port_chkready(rport)) {
		QEDF_ERR(NULL, "rport not ready\n");
		goto out;
	}

	lport = shost_priv(sc_cmd->device->host);
	qedf = (struct qedf_ctx *)lport_priv(lport);

	if ((lport->state != LPORT_ST_READY) || !(lport->link_up)) {
		QEDF_ERR(&(qedf->dbg_ctx), "link not ready.\n");
		goto out;
	}

	fcport = (struct qedf_rport *)&rp[1];

	io_req = (struct qedf_ioreq *)sc_cmd->SCp.ptr;
	if (!io_req) {
		QEDF_ERR(&(qedf->dbg_ctx), "io_req is NULL.\n");
		rc = SUCCESS;
		goto out;
	}

	QEDF_ERR(&(qedf->dbg_ctx), "Aborting io_req sc_cmd=%p xid=0x%x "
		  "fp_idx=%d.\n", sc_cmd, io_req->xid, io_req->fp_idx);

	if (qedf->stop_io_on_error) {
		qedf_stop_all_io(qedf);
		rc = SUCCESS;
		goto out;
	}

	init_completion(&io_req->abts_done);
	rval = qedf_initiate_abts(io_req, true);
	if (rval) {
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
		goto out;
	}

	wait_for_completion(&io_req->abts_done);

	if (io_req->event == QEDF_IOREQ_EV_ABORT_SUCCESS ||
	    io_req->event == QEDF_IOREQ_EV_ABORT_FAILED ||
	    io_req->event == QEDF_IOREQ_EV_CLEANUP_SUCCESS) {
		/*
		 * If we get a reponse to the abort this is success from
		 * the perspective that all references to the command have
		 * been removed from the driver and firmware
		 */
		rc = SUCCESS;
	} else {
		/* If the abort and cleanup failed then return a failure */
		rc = FAILED;
	}

	if (rc == SUCCESS)
		QEDF_ERR(&(qedf->dbg_ctx), "ABTS succeeded, xid=0x%x.\n",
			  io_req->xid);
	else
		QEDF_ERR(&(qedf->dbg_ctx), "ABTS failed, xid=0x%x.\n",
			  io_req->xid);

out:
	return rc;
}