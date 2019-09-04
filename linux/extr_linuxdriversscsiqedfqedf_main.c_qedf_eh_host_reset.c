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
struct scsi_cmnd {TYPE_1__* device; } ;
struct qedf_rport {int dummy; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  link_state; } ;
struct fc_rport_libfc_priv {int dummy; } ;
struct fc_rport {struct fc_rport_libfc_priv* dd_data; } ;
struct fc_lport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ QEDF_LINK_DOWN ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 int SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  qedf_ctx_soft_reset (struct fc_lport*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_1__*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_eh_host_reset(struct scsi_cmnd *sc_cmd)
{
	struct fc_lport *lport;
	struct qedf_ctx *qedf;
	struct fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	struct fc_rport_libfc_priv *rp = rport->dd_data;
	struct qedf_rport *fcport = (struct qedf_rport *)&rp[1];
	int rval;

	rval = fc_remote_port_chkready(rport);

	if (rval) {
		QEDF_ERR(NULL, "device_reset rport not ready\n");
		return FAILED;
	}

	if (fcport == NULL) {
		QEDF_ERR(NULL, "device_reset: rport is NULL\n");
		return FAILED;
	}

	lport = shost_priv(sc_cmd->device->host);
	qedf = lport_priv(lport);

	if (atomic_read(&qedf->link_state) == QEDF_LINK_DOWN ||
	    test_bit(QEDF_UNLOADING, &qedf->flags))
		return FAILED;

	QEDF_ERR(&(qedf->dbg_ctx), "HOST RESET Issued...");

	qedf_ctx_soft_reset(lport);

	return SUCCESS;
}