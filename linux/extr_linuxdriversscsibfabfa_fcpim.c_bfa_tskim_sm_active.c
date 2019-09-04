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
struct bfa_tskim_s {int tsk_tag; int /*<<< orphan*/  bfa; int /*<<< orphan*/  reqq_wait; TYPE_1__* itnim; } ;
typedef  enum bfa_tskim_event { ____Placeholder_bfa_tskim_event } bfa_tskim_event ;
struct TYPE_2__ {int /*<<< orphan*/  reqq; } ;

/* Variables and functions */
#define  BFA_TSKIM_SM_CLEANUP 130 
#define  BFA_TSKIM_SM_DONE 129 
#define  BFA_TSKIM_SM_HWFAIL 128 
 int /*<<< orphan*/  __bfa_cb_tskim_failed ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_tskim_cleanup_ios (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_iocdisable_ios (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_qcomp (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_tskim_send_abort (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_sm_cleanup ; 
 int /*<<< orphan*/  bfa_tskim_sm_cleanup_qfull ; 
 int /*<<< orphan*/  bfa_tskim_sm_hcb ; 
 int /*<<< orphan*/  bfa_tskim_sm_iocleanup ; 
 int /*<<< orphan*/  tm_qwait ; 

__attribute__((used)) static void
bfa_tskim_sm_active(struct bfa_tskim_s *tskim, enum bfa_tskim_event event)
{
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	switch (event) {
	case BFA_TSKIM_SM_DONE:
		bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
		bfa_tskim_cleanup_ios(tskim);
		break;

	case BFA_TSKIM_SM_CLEANUP:
		bfa_sm_set_state(tskim, bfa_tskim_sm_cleanup);
		if (!bfa_tskim_send_abort(tskim)) {
			bfa_sm_set_state(tskim, bfa_tskim_sm_cleanup_qfull);
			bfa_stats(tskim->itnim, tm_qwait);
			bfa_reqq_wait(tskim->bfa, tskim->itnim->reqq,
				&tskim->reqq_wait);
		}
		break;

	case BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		break;

	default:
		bfa_sm_fault(tskim->bfa, event);
	}
}