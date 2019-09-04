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
typedef  scalar_t__ u64 ;
struct qedf_rport {struct qedf_ctx* qedf; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {scalar_t__ cmd_type; int /*<<< orphan*/  refcount; int /*<<< orphan*/  xid; TYPE_2__* sc_cmd; int /*<<< orphan*/  abts_done; scalar_t__ return_scsi_cmd_on_abts; int /*<<< orphan*/  flags; struct qedf_rport* fcport; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; struct qedf_cmd_mgr* cmd_mgr; } ;
struct qedf_cmd_mgr {struct qedf_ioreq* cmds; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {scalar_t__ lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int FCOE_PARAMS_NUM_TASKS ; 
 scalar_t__ QEDF_ABTS ; 
 int /*<<< orphan*/  QEDF_CMD_IN_ABORT ; 
 scalar_t__ QEDF_ELS ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_flush_els_req (struct qedf_ctx*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_initiate_cleanup (struct qedf_ioreq*,int) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_scsi_done (struct qedf_ctx*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_flush_active_ios(struct qedf_rport *fcport, int lun)
{
	struct qedf_ioreq *io_req;
	struct qedf_ctx *qedf;
	struct qedf_cmd_mgr *cmd_mgr;
	int i, rc;

	if (!fcport)
		return;

	/* Check that fcport is still offloaded */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(NULL, "fcport is no longer offloaded.\n");
		return;
	}

	qedf = fcport->qedf;
	cmd_mgr = qedf->cmd_mgr;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "Flush active i/o's.\n");

	for (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) {
		io_req = &cmd_mgr->cmds[i];

		if (!io_req)
			continue;
		if (io_req->fcport != fcport)
			continue;
		if (io_req->cmd_type == QEDF_ELS) {
			rc = kref_get_unless_zero(&io_req->refcount);
			if (!rc) {
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for ELS io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				continue;
			}
			qedf_flush_els_req(qedf, io_req);
			/*
			 * Release the kref and go back to the top of the
			 * loop.
			 */
			goto free_cmd;
		}

		if (io_req->cmd_type == QEDF_ABTS) {
			rc = kref_get_unless_zero(&io_req->refcount);
			if (!rc) {
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for abort io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				continue;
			}
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			    "Flushing abort xid=0x%x.\n", io_req->xid);

			clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);

			if (io_req->sc_cmd) {
				if (io_req->return_scsi_cmd_on_abts)
					qedf_scsi_done(qedf, io_req, DID_ERROR);
			}

			/* Notify eh_abort handler that ABTS is complete */
			complete(&io_req->abts_done);
			kref_put(&io_req->refcount, qedf_release_cmd);

			goto free_cmd;
		}

		if (!io_req->sc_cmd)
			continue;
		if (lun > 0) {
			if (io_req->sc_cmd->device->lun !=
			    (u64)lun)
				continue;
		}

		/*
		 * Use kref_get_unless_zero in the unlikely case the command
		 * we're about to flush was completed in the normal SCSI path
		 */
		rc = kref_get_unless_zero(&io_req->refcount);
		if (!rc) {
			QEDF_ERR(&(qedf->dbg_ctx), "Could not get kref for "
			    "io_req=0x%p xid=0x%x\n", io_req, io_req->xid);
			continue;
		}
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Cleanup xid=0x%x.\n", io_req->xid);

		/* Cleanup task and return I/O mid-layer */
		qedf_initiate_cleanup(io_req, true);

free_cmd:
		kref_put(&io_req->refcount, qedf_release_cmd);
	}
}