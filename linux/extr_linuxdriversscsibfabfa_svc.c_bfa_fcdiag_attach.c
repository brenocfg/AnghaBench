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
struct bfa_s {int /*<<< orphan*/  trcmod; } ;
struct bfa_pcidev_s {int dummy; } ;
struct bfa_iocfc_cfg_s {int dummy; } ;
struct bfa_dport_s {int /*<<< orphan*/  result; int /*<<< orphan*/  test_state; int /*<<< orphan*/ * cbarg; int /*<<< orphan*/ * cbfn; int /*<<< orphan*/  reqq_wait; struct bfa_s* bfa; } ;
struct bfa_fcdiag_s {int /*<<< orphan*/  trcmod; struct bfa_s* bfa; struct bfa_dport_s dport; } ;
struct bfa_diag_dport_result_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DPORT_ST_DISABLED ; 
 struct bfa_fcdiag_s* BFA_FCDIAG_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_dport_qresume ; 
 int /*<<< orphan*/  bfa_dport_sm_disabled ; 
 int /*<<< orphan*/  bfa_reqq_winit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_dport_s*) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
bfa_fcdiag_attach(struct bfa_s *bfa, void *bfad, struct bfa_iocfc_cfg_s *cfg,
		struct bfa_pcidev_s *pcidev)
{
	struct bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	struct bfa_dport_s  *dport = &fcdiag->dport;

	fcdiag->bfa             = bfa;
	fcdiag->trcmod  = bfa->trcmod;
	/* The common DIAG attach bfa_diag_attach() will do all memory claim */
	dport->bfa = bfa;
	bfa_sm_set_state(dport, bfa_dport_sm_disabled);
	bfa_reqq_winit(&dport->reqq_wait, bfa_dport_qresume, dport);
	dport->cbfn = NULL;
	dport->cbarg = NULL;
	dport->test_state = BFA_DPORT_ST_DISABLED;
	memset(&dport->result, 0, sizeof(struct bfa_diag_dport_result_s));
}