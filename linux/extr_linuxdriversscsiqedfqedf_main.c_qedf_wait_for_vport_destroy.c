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
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_1__* lport; } ;
struct fc_host_attrs {scalar_t__ npiv_vports_inuse; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_NPIV ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct fc_host_attrs* shost_to_fc_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_wait_for_vport_destroy(struct qedf_ctx *qedf)
{
	struct fc_host_attrs *fc_host = shost_to_fc_host(qedf->lport->host);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_NPIV,
	    "Entered.\n");
	while (fc_host->npiv_vports_inuse > 0) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_NPIV,
		    "Waiting for all vports to be reaped.\n");
		msleep(1000);
	}
}