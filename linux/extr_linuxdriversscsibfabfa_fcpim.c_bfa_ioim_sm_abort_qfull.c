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
struct bfa_ioim_s {int iotag; int /*<<< orphan*/  bfa; int /*<<< orphan*/  hcb_qe; TYPE_1__* iosp; } ;
typedef  enum bfa_ioim_event { ____Placeholder_bfa_ioim_event } bfa_ioim_event ;
struct TYPE_2__ {int /*<<< orphan*/  reqq_wait; int /*<<< orphan*/  abort_explicit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
#define  BFA_IOIM_SM_CLEANUP 133 
#define  BFA_IOIM_SM_COMP 132 
#define  BFA_IOIM_SM_COMP_GOOD 131 
#define  BFA_IOIM_SM_DONE 130 
#define  BFA_IOIM_SM_HWFAIL 129 
#define  BFA_IOIM_SM_QRESUME 128 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __bfa_cb_ioim_abort ; 
 int /*<<< orphan*/  __bfa_cb_ioim_failed ; 
 int /*<<< orphan*/  bfa_cb_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_move_to_comp_q (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_send_abort (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sm_abort ; 
 int /*<<< orphan*/  bfa_ioim_sm_cleanup_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb_free ; 
 int /*<<< orphan*/  bfa_reqq_wcancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_ioim_sm_abort_qfull(struct bfa_ioim_s *ioim, enum bfa_ioim_event event)
{
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	switch (event) {
	case BFA_IOIM_SM_QRESUME:
		bfa_sm_set_state(ioim, bfa_ioim_sm_abort);
		bfa_ioim_send_abort(ioim);
		break;

	case BFA_IOIM_SM_CLEANUP:
		WARN_ON(ioim->iosp->abort_explicit != BFA_TRUE);
		ioim->iosp->abort_explicit = BFA_FALSE;
		bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
		break;

	case BFA_IOIM_SM_COMP_GOOD:
	case BFA_IOIM_SM_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_wait);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_abort,
			      ioim);
		break;

	case BFA_IOIM_SM_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_free);
		bfa_reqq_wcancel(&ioim->iosp->reqq_wait);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_abort,
			      ioim);
		break;

	case BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_wait);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		break;

	default:
		bfa_sm_fault(ioim->bfa, event);
	}
}