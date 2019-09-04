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
struct bfa_lps_s {int bfa_tag; int /*<<< orphan*/  bfa; int /*<<< orphan*/  wqe; } ;
typedef  enum bfa_lps_event { ____Placeholder_bfa_lps_event } bfa_lps_event ;

/* Variables and functions */
#define  BFA_LPS_SM_DELETE 131 
#define  BFA_LPS_SM_OFFLINE 130 
#define  BFA_LPS_SM_RESUME 129 
#define  BFA_LPS_SM_RX_CVL 128 
 int /*<<< orphan*/  bfa_lps_send_login (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_init ; 
 int /*<<< orphan*/  bfa_lps_sm_login ; 
 int /*<<< orphan*/  bfa_reqq_wcancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_lps_sm_loginwait(struct bfa_lps_s *lps, enum bfa_lps_event event)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	switch (event) {
	case BFA_LPS_SM_RESUME:
		bfa_sm_set_state(lps, bfa_lps_sm_login);
		bfa_lps_send_login(lps);
		break;

	case BFA_LPS_SM_OFFLINE:
	case BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);
		break;

	case BFA_LPS_SM_RX_CVL:
		/*
		 * Login was not even sent out; so when getting out
		 * of this state, it will appear like a login retry
		 * after Clear virtual link
		 */
		break;

	default:
		bfa_sm_fault(lps->bfa, event);
	}
}