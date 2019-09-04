#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_tskim_s {int tsk_tag; int /*<<< orphan*/  bfa; int /*<<< orphan*/  reqq_wait; TYPE_1__* itnim; int /*<<< orphan*/  tsk_status; } ;
typedef  enum bfa_tskim_event { ____Placeholder_bfa_tskim_event } bfa_tskim_event ;
struct TYPE_3__ {int /*<<< orphan*/  reqq; } ;

/* Variables and functions */
#define  BFA_TSKIM_SM_START 128 
 int /*<<< orphan*/  BFI_TSKIM_STS_OK ; 
 int /*<<< orphan*/  bfa_itnim_is_online (TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_tskim_cleanup_ios (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_gather_ios (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_send (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_sm_active ; 
 int /*<<< orphan*/  bfa_tskim_sm_iocleanup ; 
 int /*<<< orphan*/  bfa_tskim_sm_qfull ; 
 int /*<<< orphan*/  tm_qwait ; 

__attribute__((used)) static void
bfa_tskim_sm_uninit(struct bfa_tskim_s *tskim, enum bfa_tskim_event event)
{
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	switch (event) {
	case BFA_TSKIM_SM_START:
		bfa_sm_set_state(tskim, bfa_tskim_sm_active);
		bfa_tskim_gather_ios(tskim);

		/*
		 * If device is offline, do not send TM on wire. Just cleanup
		 * any pending IO requests and complete TM request.
		 */
		if (!bfa_itnim_is_online(tskim->itnim)) {
			bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
			tskim->tsk_status = BFI_TSKIM_STS_OK;
			bfa_tskim_cleanup_ios(tskim);
			return;
		}

		if (!bfa_tskim_send(tskim)) {
			bfa_sm_set_state(tskim, bfa_tskim_sm_qfull);
			bfa_stats(tskim->itnim, tm_qwait);
			bfa_reqq_wait(tskim->bfa, tskim->itnim->reqq,
					  &tskim->reqq_wait);
		}
		break;

	default:
		bfa_sm_fault(tskim->bfa, event);
	}
}