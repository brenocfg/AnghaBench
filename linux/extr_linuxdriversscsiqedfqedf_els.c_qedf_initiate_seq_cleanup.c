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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct qedf_rport {int /*<<< orphan*/  rport_lock; struct fcoe_wqe* sq; TYPE_1__* qedf; } ;
struct qedf_ioreq {TYPE_2__* task_params; struct qedf_els_cb_arg* cb_arg; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  refcount; int /*<<< orphan*/  xid; struct qedf_rport* fcport; } ;
struct qedf_els_cb_arg {int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  offset; } ;
struct fcoe_wqe {int dummy; } ;
struct TYPE_4__ {struct fcoe_wqe* sqe; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int HZ ; 
 int QEDF_CLEANUP_TIMEOUT ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  QEDF_SEQ_CLEANUP ; 
 int /*<<< orphan*/  init_initiator_sequence_recovery_fcoe_task (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct qedf_els_cb_arg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcoe_wqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_cmd_timer_set (TYPE_1__*,struct qedf_ioreq*,int) ; 
 size_t qedf_get_sqe_idx (struct qedf_rport*) ; 
 int /*<<< orphan*/  qedf_ring_doorbell (struct qedf_rport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qedf_initiate_seq_cleanup(struct qedf_ioreq *orig_io_req,
	u32 offset, u8 r_ctl)
{
	struct qedf_rport *fcport;
	unsigned long flags;
	struct qedf_els_cb_arg *cb_arg;
	struct fcoe_wqe *sqe;
	u16 sqe_idx;

	fcport = orig_io_req->fcport;

	QEDF_INFO(&(fcport->qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Doing sequence cleanup for xid=0x%x offset=%u.\n",
	    orig_io_req->xid, offset);

	cb_arg = kzalloc(sizeof(struct qedf_els_cb_arg), GFP_NOIO);
	if (!cb_arg) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Unable to allocate cb_arg "
			  "for sequence cleanup\n");
		return;
	}

	/* Get reference for cleanup request */
	kref_get(&orig_io_req->refcount);

	orig_io_req->cmd_type = QEDF_SEQ_CLEANUP;
	cb_arg->offset = offset;
	cb_arg->r_ctl = r_ctl;
	orig_io_req->cb_arg = cb_arg;

	qedf_cmd_timer_set(fcport->qedf, orig_io_req,
	    QEDF_CLEANUP_TIMEOUT * HZ);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	memset(sqe, 0, sizeof(struct fcoe_wqe));
	orig_io_req->task_params->sqe = sqe;

	init_initiator_sequence_recovery_fcoe_task(orig_io_req->task_params,
						   offset);
	qedf_ring_doorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
}