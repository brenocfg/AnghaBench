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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct qedf_rport {int /*<<< orphan*/  free_sqes; int /*<<< orphan*/  num_active_ios; struct qedf_ctx* qedf; } ;
struct qedf_ioreq {size_t xid; int rx_id; scalar_t__ tx_buf_off; scalar_t__ rx_buf_off; scalar_t__ tm_flags; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  refcount; struct io_bdt* bd_tbl; struct qedf_rport* fcport; struct qedf_cmd_mgr* cmd_mgr; int /*<<< orphan*/  flags; } ;
struct qedf_ctx {int /*<<< orphan*/  alloc_failures; int /*<<< orphan*/  dbg_ctx; struct qedf_cmd_mgr* cmd_mgr; } ;
struct qedf_cmd_mgr {size_t idx; struct io_bdt** io_bdt_pool; int /*<<< orphan*/  free_list_cnt; int /*<<< orphan*/  lock; struct qedf_ioreq* cmds; } ;
struct io_bdt {struct qedf_ioreq* io_req; } ;

/* Variables and functions */
 int FCOE_PARAMS_NUM_TASKS ; 
 scalar_t__ GBL_RSVD_TASKS ; 
 scalar_t__ NUM_RW_TASKS_PER_CONNECTION ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct qedf_ioreq *qedf_alloc_cmd(struct qedf_rport *fcport, u8 cmd_type)
{
	struct qedf_ctx *qedf = fcport->qedf;
	struct qedf_cmd_mgr *cmd_mgr = qedf->cmd_mgr;
	struct qedf_ioreq *io_req = NULL;
	struct io_bdt *bd_tbl;
	u16 xid;
	uint32_t free_sqes;
	int i;
	unsigned long flags;

	free_sqes = atomic_read(&fcport->free_sqes);

	if (!free_sqes) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, free_sqes=%d.\n ",
		    free_sqes);
		goto out_failed;
	}

	/* Limit the number of outstanding R/W tasks */
	if ((atomic_read(&fcport->num_active_ios) >=
	    NUM_RW_TASKS_PER_CONNECTION)) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, num_active_ios=%d.\n",
		    atomic_read(&fcport->num_active_ios));
		goto out_failed;
	}

	/* Limit global TIDs certain tasks */
	if (atomic_read(&cmd_mgr->free_list_cnt) <= GBL_RSVD_TASKS) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Returning NULL, free_list_cnt=%d.\n",
		    atomic_read(&cmd_mgr->free_list_cnt));
		goto out_failed;
	}

	spin_lock_irqsave(&cmd_mgr->lock, flags);
	for (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) {
		io_req = &cmd_mgr->cmds[cmd_mgr->idx];
		cmd_mgr->idx++;
		if (cmd_mgr->idx == FCOE_PARAMS_NUM_TASKS)
			cmd_mgr->idx = 0;

		/* Check to make sure command was previously freed */
		if (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags))
			break;
	}

	if (i == FCOE_PARAMS_NUM_TASKS) {
		spin_unlock_irqrestore(&cmd_mgr->lock, flags);
		goto out_failed;
	}

	set_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);
	spin_unlock_irqrestore(&cmd_mgr->lock, flags);

	atomic_inc(&fcport->num_active_ios);
	atomic_dec(&fcport->free_sqes);
	xid = io_req->xid;
	atomic_dec(&cmd_mgr->free_list_cnt);

	io_req->cmd_mgr = cmd_mgr;
	io_req->fcport = fcport;

	/* Hold the io_req against deletion */
	kref_init(&io_req->refcount);

	/* Bind io_bdt for this io_req */
	/* Have a static link between io_req and io_bdt_pool */
	bd_tbl = io_req->bd_tbl = cmd_mgr->io_bdt_pool[xid];
	if (bd_tbl == NULL) {
		QEDF_ERR(&(qedf->dbg_ctx), "bd_tbl is NULL, xid=%x.\n", xid);
		kref_put(&io_req->refcount, qedf_release_cmd);
		goto out_failed;
	}
	bd_tbl->io_req = io_req;
	io_req->cmd_type = cmd_type;
	io_req->tm_flags = 0;

	/* Reset sequence offset data */
	io_req->rx_buf_off = 0;
	io_req->tx_buf_off = 0;
	io_req->rx_id = 0xffff; /* No OX_ID */

	return io_req;

out_failed:
	/* Record failure for stats and return NULL to caller */
	qedf->alloc_failures++;
	return NULL;
}