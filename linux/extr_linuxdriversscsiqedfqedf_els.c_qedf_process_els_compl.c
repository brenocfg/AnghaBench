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
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  resp_len; } ;
struct qedf_ioreq {int /*<<< orphan*/  refcount; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/  (* cb_func ) (int /*<<< orphan*/ *) ;TYPE_2__ mp_req; struct scsi_cmnd* sc_cmd; int /*<<< orphan*/  xid; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  cmd_type; } ;
struct qedf_ctx {int /*<<< orphan*/  tasks; int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_task_context {int dummy; } ;
struct fcoe_cqe_midpath_info {int /*<<< orphan*/  data_placement_size; } ;
struct TYPE_3__ {struct fcoe_cqe_midpath_info midpath_info; } ;
struct fcoe_cqe {TYPE_1__ cqe_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fcoe_task_context* qedf_get_task_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void qedf_process_els_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *els_req)
{
	struct fcoe_task_context *task_ctx;
	struct scsi_cmnd *sc_cmd;
	uint16_t xid;
	struct fcoe_cqe_midpath_info *mp_info;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered with xid = 0x%x"
		   " cmd_type = %d.\n", els_req->xid, els_req->cmd_type);

	/* Kill the ELS timer */
	cancel_delayed_work(&els_req->timeout_work);

	xid = els_req->xid;
	task_ctx = qedf_get_task_mem(&qedf->tasks, xid);
	sc_cmd = els_req->sc_cmd;

	/* Get ELS response length from CQE */
	mp_info = &cqe->cqe_info.midpath_info;
	els_req->mp_req.resp_len = mp_info->data_placement_size;

	/* Parse ELS response */
	if ((els_req->cb_func) && (els_req->cb_arg)) {
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = NULL;
	}

	kref_put(&els_req->refcount, qedf_release_cmd);
}