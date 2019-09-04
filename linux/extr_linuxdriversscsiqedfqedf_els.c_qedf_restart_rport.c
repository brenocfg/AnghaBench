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
typedef  struct qedf_rport* u32 ;
struct qedf_rport {int /*<<< orphan*/  flags; TYPE_2__* qedf; struct fc_rport_priv* rdata; } ;
struct TYPE_3__ {struct qedf_rport* port_id; } ;
struct fc_rport_priv {TYPE_1__ ids; } ;
struct fc_lport {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dbg_ctx; struct fc_lport* lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,struct qedf_rport*) ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_RESET ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  QEDF_RPORT_UPLOADING_CONNECTION ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fc_rport_priv* fc_rport_create (struct fc_lport*,struct qedf_rport*) ; 
 int /*<<< orphan*/  fc_rport_login (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_logoff (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_restart_rport(struct qedf_rport *fcport)
{
	struct fc_lport *lport;
	struct fc_rport_priv *rdata;
	u32 port_id;

	if (!fcport)
		return;

	if (test_bit(QEDF_RPORT_IN_RESET, &fcport->flags) ||
	    !test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "fcport %p already in reset or not offloaded.\n",
		    fcport);
		return;
	}

	/* Set that we are now in reset */
	set_bit(QEDF_RPORT_IN_RESET, &fcport->flags);

	rdata = fcport->rdata;
	if (rdata) {
		lport = fcport->qedf->lport;
		port_id = rdata->ids.port_id;
		QEDF_ERR(&(fcport->qedf->dbg_ctx),
		    "LOGO port_id=%x.\n", port_id);
		fc_rport_logoff(rdata);
		/* Recreate the rport and log back in */
		rdata = fc_rport_create(lport, port_id);
		if (rdata)
			fc_rport_login(rdata);
	}
	clear_bit(QEDF_RPORT_IN_RESET, &fcport->flags);
}