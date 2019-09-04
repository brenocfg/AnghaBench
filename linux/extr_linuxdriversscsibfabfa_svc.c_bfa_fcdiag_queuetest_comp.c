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
struct TYPE_4__ {scalar_t__ timer_active; scalar_t__ count; scalar_t__ all; int queue; scalar_t__ status; scalar_t__ lock; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  timer; struct bfa_diag_qtest_result_s* result; } ;
struct bfa_fcdiag_s {TYPE_1__ qtest; } ;
struct bfa_diag_qtest_result_s {scalar_t__ status; int queue; scalar_t__ count; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ bfi_diag_qtest_rsp_t ;
typedef  scalar_t__ bfa_status_t ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_DATACORRUPTED ; 
 scalar_t__ BFA_STATUS_OK ; 
 int BFI_IOC_MAX_CQS ; 
 int BFI_LMSG_PL_WSZ ; 
 void* QTEST_CNT_DEFAULT ; 
 int /*<<< orphan*/  QTEST_PAT_DEFAULT ; 
 scalar_t__ bfa_fcdiag_queuetest_send (struct bfa_fcdiag_s*) ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcdiag_s*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bfa_fcdiag_queuetest_comp(struct bfa_fcdiag_s *fcdiag,
			bfi_diag_qtest_rsp_t *rsp)
{
	struct bfa_diag_qtest_result_s *res = fcdiag->qtest.result;
	bfa_status_t status = BFA_STATUS_OK;
	int i;

	/* Check timer, should still be active   */
	if (!fcdiag->qtest.timer_active) {
		bfa_trc(fcdiag, fcdiag->qtest.timer_active);
		return;
	}

	/* update count */
	fcdiag->qtest.count--;

	/* Check result */
	for (i = 0; i < BFI_LMSG_PL_WSZ; i++) {
		if (rsp->data[i] != ~(QTEST_PAT_DEFAULT)) {
			res->status = BFA_STATUS_DATACORRUPTED;
			break;
		}
	}

	if (res->status == BFA_STATUS_OK) {
		if (fcdiag->qtest.count > 0) {
			status = bfa_fcdiag_queuetest_send(fcdiag);
			if (status == BFA_STATUS_OK)
				return;
			else
				res->status = status;
		} else if (fcdiag->qtest.all > 0 &&
			fcdiag->qtest.queue < (BFI_IOC_MAX_CQS - 1)) {
			fcdiag->qtest.count = QTEST_CNT_DEFAULT;
			fcdiag->qtest.queue++;
			status = bfa_fcdiag_queuetest_send(fcdiag);
			if (status == BFA_STATUS_OK)
				return;
			else
				res->status = status;
		}
	}

	/* Stop timer when we comp all queue */
	if (fcdiag->qtest.timer_active) {
		bfa_timer_stop(&fcdiag->qtest.timer);
		fcdiag->qtest.timer_active = 0;
	}
	res->queue = fcdiag->qtest.queue;
	res->count = QTEST_CNT_DEFAULT - fcdiag->qtest.count;
	bfa_trc(fcdiag, res->count);
	bfa_trc(fcdiag, res->status);
	fcdiag->qtest.status = res->status;
	fcdiag->qtest.cbfn(fcdiag->qtest.cbarg, fcdiag->qtest.status);
	fcdiag->qtest.lock = 0;
}