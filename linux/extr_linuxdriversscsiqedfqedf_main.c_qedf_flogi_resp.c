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
struct qedf_ctx {int /*<<< orphan*/  flogi_compl; int /*<<< orphan*/  flogi_failed; int /*<<< orphan*/  dbg_ctx; } ;
struct fc_seq {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {struct fc_lport* lp; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 scalar_t__ ELS_LS_RJT ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_flogi_resp (struct fc_seq*,struct fc_frame*,struct fc_lport*) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  qedf_set_data_src_addr (struct qedf_ctx*,struct fc_frame*) ; 

__attribute__((used)) static void qedf_flogi_resp(struct fc_seq *seq, struct fc_frame *fp,
	void *arg)
{
	struct fc_exch *exch = fc_seq_exch(seq);
	struct fc_lport *lport = exch->lp;
	struct qedf_ctx *qedf = lport_priv(lport);

	if (!qedf) {
		QEDF_ERR(NULL, "qedf is NULL.\n");
		return;
	}

	/*
	 * If ERR_PTR is set then don't try to stat anything as it will cause
	 * a crash when we access fp.
	 */
	if (IS_ERR(fp)) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
		    "fp has IS_ERR() set.\n");
		goto skip_stat;
	}

	/* Log stats for FLOGI reject */
	if (fc_frame_payload_op(fp) == ELS_LS_RJT)
		qedf->flogi_failed++;
	else if (fc_frame_payload_op(fp) == ELS_LS_ACC) {
		/* Set the source MAC we will use for FCoE traffic */
		qedf_set_data_src_addr(qedf, fp);
	}

	/* Complete flogi_compl so we can proceed to sending ADISCs */
	complete(&qedf->flogi_compl);

skip_stat:
	/* Report response to libfc */
	fc_lport_flogi_resp(seq, fp, lport);
}