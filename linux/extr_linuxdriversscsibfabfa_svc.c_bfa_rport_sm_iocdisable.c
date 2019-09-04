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
struct bfa_rport_s {int rport_tag; int /*<<< orphan*/  bfa; } ;
typedef  enum bfa_rport_event { ____Placeholder_bfa_rport_event } bfa_rport_event ;

/* Variables and functions */
#define  BFA_RPORT_SM_DELETE 131 
#define  BFA_RPORT_SM_HWFAIL 130 
#define  BFA_RPORT_SM_OFFLINE 129 
#define  BFA_RPORT_SM_ONLINE 128 
 int /*<<< orphan*/  bfa_rport_free (struct bfa_rport_s*) ; 
 int /*<<< orphan*/  bfa_rport_offline_cb (struct bfa_rport_s*) ; 
 int /*<<< orphan*/  bfa_rport_send_fwcreate (struct bfa_rport_s*) ; 
 int /*<<< orphan*/  bfa_rport_sm_fwcreate ; 
 int /*<<< orphan*/  bfa_rport_sm_fwcreate_qfull ; 
 int /*<<< orphan*/  bfa_rport_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm_iocd_del ; 
 int /*<<< orphan*/  sm_iocd_off ; 
 int /*<<< orphan*/  sm_iocd_on ; 
 int /*<<< orphan*/  sm_iocd_unexp ; 

__attribute__((used)) static void
bfa_rport_sm_iocdisable(struct bfa_rport_s *rp, enum bfa_rport_event event)
{
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	switch (event) {
	case BFA_RPORT_SM_OFFLINE:
		bfa_stats(rp, sm_iocd_off);
		bfa_rport_offline_cb(rp);
		break;

	case BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_iocd_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_free(rp);
		break;

	case BFA_RPORT_SM_ONLINE:
		bfa_stats(rp, sm_iocd_on);
		if (bfa_rport_send_fwcreate(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		else
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate_qfull);
		break;

	case BFA_RPORT_SM_HWFAIL:
		break;

	default:
		bfa_stats(rp, sm_iocd_unexp);
		bfa_sm_fault(rp->bfa, event);
	}
}