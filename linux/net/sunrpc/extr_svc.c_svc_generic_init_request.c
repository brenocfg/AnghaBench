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
struct svc_version {size_t vs_nproc; int /*<<< orphan*/  vs_dispatch; int /*<<< orphan*/ * vs_count; struct svc_procedure* vs_proc; scalar_t__ vs_need_cong_ctrl; } ;
struct svc_rqst {size_t rq_vers; size_t rq_proc; int /*<<< orphan*/  rq_resp; int /*<<< orphan*/  rq_argp; struct svc_procedure const* rq_procinfo; TYPE_1__* rq_xprt; } ;
struct svc_program {size_t pg_nvers; int /*<<< orphan*/  pg_hivers; int /*<<< orphan*/  pg_lovers; struct svc_version** pg_vers; } ;
struct TYPE_4__ {int /*<<< orphan*/  hivers; int /*<<< orphan*/  lovers; } ;
struct svc_process_info {TYPE_2__ mismatch; int /*<<< orphan*/  dispatch; } ;
struct svc_procedure {int /*<<< orphan*/  pc_ressize; int /*<<< orphan*/  pc_argsize; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  xpt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_CONG_CTRL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_proc_unavail ; 
 int /*<<< orphan*/  rpc_prog_mismatch ; 
 int /*<<< orphan*/  rpc_success ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__be32
svc_generic_init_request(struct svc_rqst *rqstp,
		const struct svc_program *progp,
		struct svc_process_info *ret)
{
	const struct svc_version *versp = NULL;	/* compiler food */
	const struct svc_procedure *procp = NULL;

	if (rqstp->rq_vers >= progp->pg_nvers )
		goto err_bad_vers;
	versp = progp->pg_vers[rqstp->rq_vers];
	if (!versp)
		goto err_bad_vers;

	/*
	 * Some protocol versions (namely NFSv4) require some form of
	 * congestion control.  (See RFC 7530 section 3.1 paragraph 2)
	 * In other words, UDP is not allowed. We mark those when setting
	 * up the svc_xprt, and verify that here.
	 *
	 * The spec is not very clear about what error should be returned
	 * when someone tries to access a server that is listening on UDP
	 * for lower versions. RPC_PROG_MISMATCH seems to be the closest
	 * fit.
	 */
	if (versp->vs_need_cong_ctrl && rqstp->rq_xprt &&
	    !test_bit(XPT_CONG_CTRL, &rqstp->rq_xprt->xpt_flags))
		goto err_bad_vers;

	if (rqstp->rq_proc >= versp->vs_nproc)
		goto err_bad_proc;
	rqstp->rq_procinfo = procp = &versp->vs_proc[rqstp->rq_proc];
	if (!procp)
		goto err_bad_proc;

	/* Initialize storage for argp and resp */
	memset(rqstp->rq_argp, 0, procp->pc_argsize);
	memset(rqstp->rq_resp, 0, procp->pc_ressize);

	/* Bump per-procedure stats counter */
	versp->vs_count[rqstp->rq_proc]++;

	ret->dispatch = versp->vs_dispatch;
	return rpc_success;
err_bad_vers:
	ret->mismatch.lovers = progp->pg_lovers;
	ret->mismatch.hivers = progp->pg_hivers;
	return rpc_prog_mismatch;
err_bad_proc:
	return rpc_proc_unavail;
}