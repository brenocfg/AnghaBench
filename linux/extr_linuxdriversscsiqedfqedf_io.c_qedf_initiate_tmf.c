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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct qedf_rport {struct qedf_ctx* qedf; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  flags; struct fc_lport* lport; } ;
struct fc_rport_libfc_priv {int dummy; } ;
struct fc_rport {struct fc_rport_libfc_priv* dd_data; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  link_up; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  QEDF_DBG_STOP_IO ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 int SUCCESS ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 int qedf_execute_tmf (struct qedf_rport*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qedf_initiate_tmf(struct scsi_cmnd *sc_cmd, u8 tm_flags)
{
	struct fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	struct fc_rport_libfc_priv *rp = rport->dd_data;
	struct qedf_rport *fcport = (struct qedf_rport *)&rp[1];
	struct qedf_ctx *qedf;
	struct fc_lport *lport;
	int rc = SUCCESS;
	int rval;

	rval = fc_remote_port_chkready(rport);

	if (rval) {
		QEDF_ERR(NULL, "device_reset rport not ready\n");
		rc = FAILED;
		goto tmf_err;
	}

	if (fcport == NULL) {
		QEDF_ERR(NULL, "device_reset: rport is NULL\n");
		rc = FAILED;
		goto tmf_err;
	}

	qedf = fcport->qedf;
	lport = qedf->lport;

	if (test_bit(QEDF_UNLOADING, &qedf->flags) ||
	    test_bit(QEDF_DBG_STOP_IO, &qedf->flags)) {
		rc = SUCCESS;
		goto tmf_err;
	}

	if (lport->state != LPORT_ST_READY || !(lport->link_up)) {
		QEDF_ERR(&(qedf->dbg_ctx), "link is not ready\n");
		rc = FAILED;
		goto tmf_err;
	}

	rc = qedf_execute_tmf(fcport, sc_cmd, tm_flags);

tmf_err:
	return rc;
}