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
struct bfa_s {int dummy; } ;
struct bfa_fcxp_wqe_s {int /*<<< orphan*/  qe; } ;
struct bfa_fcxp_mod_s {int /*<<< orphan*/  rsp_wait_q; int /*<<< orphan*/  req_wait_q; } ;

/* Variables and functions */
 struct bfa_fcxp_mod_s* BFA_FCXP_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_fcxp_wqe_s*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_fcxp_walloc_cancel(struct bfa_s *bfa, struct bfa_fcxp_wqe_s *wqe)
{
	struct bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->req_wait_q, wqe) ||
		!bfa_q_is_on_q(&mod->rsp_wait_q, wqe));
	list_del(&wqe->qe);
}