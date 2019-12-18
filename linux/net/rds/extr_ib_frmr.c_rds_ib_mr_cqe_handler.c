#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rds_ib_frmr {int fr_inv; int fr_reg; int /*<<< orphan*/  fr_reg_done; int /*<<< orphan*/  fr_inv_done; } ;
struct TYPE_4__ {struct rds_ib_frmr frmr; } ;
struct rds_ib_mr {TYPE_1__ u; } ;
struct rds_ib_connection {int /*<<< orphan*/  i_fastreg_wrs; TYPE_2__* conn; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  vendor_err; scalar_t__ wr_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRMR_IS_FREE ; 
 int /*<<< orphan*/  FRMR_IS_INUSE ; 
 int /*<<< orphan*/  FRMR_IS_STALE ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_wc_status_msg (scalar_t__) ; 
 scalar_t__ rds_conn_up (TYPE_2__*) ; 
 int /*<<< orphan*/  rds_ib_conn_error (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_transition_frwr_state (struct rds_ib_mr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void rds_ib_mr_cqe_handler(struct rds_ib_connection *ic, struct ib_wc *wc)
{
	struct rds_ib_mr *ibmr = (void *)(unsigned long)wc->wr_id;
	struct rds_ib_frmr *frmr = &ibmr->u.frmr;

	if (wc->status != IB_WC_SUCCESS) {
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_STALE);
		if (rds_conn_up(ic->conn))
			rds_ib_conn_error(ic->conn,
					  "frmr completion <%pI4,%pI4> status %u(%s), vendor_err 0x%x, disconnecting and reconnecting\n",
					  &ic->conn->c_laddr,
					  &ic->conn->c_faddr,
					  wc->status,
					  ib_wc_status_msg(wc->status),
					  wc->vendor_err);
	}

	if (frmr->fr_inv) {
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_FREE);
		frmr->fr_inv = false;
		wake_up(&frmr->fr_inv_done);
	}

	if (frmr->fr_reg) {
		frmr->fr_reg = false;
		wake_up(&frmr->fr_reg_done);
	}

	/* enforce order of frmr->{fr_reg,fr_inv} update
	 * before incrementing i_fastreg_wrs
	 */
	smp_mb__before_atomic();
	atomic_inc(&ic->i_fastreg_wrs);
}