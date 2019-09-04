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
struct bfa_fcxp_wqe_s {int /*<<< orphan*/  alloc_cbarg; int /*<<< orphan*/  (* alloc_cbfn ) (int /*<<< orphan*/ ,struct bfa_fcxp_s*) ;int /*<<< orphan*/  rsp_sglen_cbfn; int /*<<< orphan*/  rsp_sga_cbfn; int /*<<< orphan*/  req_sglen_cbfn; int /*<<< orphan*/  req_sga_cbfn; int /*<<< orphan*/  nrsp_sgles; int /*<<< orphan*/  nreq_sgles; int /*<<< orphan*/  bfa; int /*<<< orphan*/  caller; } ;
struct bfa_fcxp_s {int /*<<< orphan*/  qe; scalar_t__ req_rsp; int /*<<< orphan*/  fcxp_tag; struct bfa_fcxp_mod_s* fcxp_mod; } ;
struct bfa_fcxp_mod_s {int /*<<< orphan*/  fcxp_rsp_free_q; int /*<<< orphan*/  fcxp_req_free_q; int /*<<< orphan*/  fcxp_active_q; int /*<<< orphan*/  bfa; int /*<<< orphan*/  rsp_wait_q; int /*<<< orphan*/  req_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcxp_init (struct bfa_fcxp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_fcxp_wqe_s**) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bfa_fcxp_s*) ; 

__attribute__((used)) static void
bfa_fcxp_put(struct bfa_fcxp_s *fcxp)
{
	struct bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	struct bfa_fcxp_wqe_s *wqe;

	if (fcxp->req_rsp)
		bfa_q_deq(&mod->req_wait_q, &wqe);
	else
		bfa_q_deq(&mod->rsp_wait_q, &wqe);

	if (wqe) {
		bfa_trc(mod->bfa, fcxp->fcxp_tag);

		bfa_fcxp_init(fcxp, wqe->caller, wqe->bfa, wqe->nreq_sgles,
			wqe->nrsp_sgles, wqe->req_sga_cbfn,
			wqe->req_sglen_cbfn, wqe->rsp_sga_cbfn,
			wqe->rsp_sglen_cbfn);

		wqe->alloc_cbfn(wqe->alloc_cbarg, fcxp);
		return;
	}

	WARN_ON(!bfa_q_is_on_q(&mod->fcxp_active_q, fcxp));
	list_del(&fcxp->qe);

	if (fcxp->req_rsp)
		list_add_tail(&fcxp->qe, &mod->fcxp_req_free_q);
	else
		list_add_tail(&fcxp->qe, &mod->fcxp_rsp_free_q);
}