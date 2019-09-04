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
struct TYPE_3__ {int state; } ;
struct TYPE_4__ {TYPE_1__ scn; } ;
struct bfa_dport_s {int /*<<< orphan*/  bfa; TYPE_2__ i2hmsg; int /*<<< orphan*/  dynamic; } ;
typedef  enum bfa_dport_sm_event { ____Placeholder_bfa_dport_sm_event } bfa_dport_sm_event ;

/* Variables and functions */
#define  BFA_DPORT_SM_HWFAIL 130 
#define  BFA_DPORT_SM_SCN 129 
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  BFI_DPORT_SCN_DDPORT_DISABLED 128 
 int /*<<< orphan*/  bfa_cb_fcdiag_dport (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_sm_disabled ; 
 int /*<<< orphan*/  bfa_fcport_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dport_sm_dynamic_disabling(struct bfa_dport_s *dport,
			       enum bfa_dport_sm_event event)
{
	bfa_trc(dport->bfa, event);

	switch (event) {
	case BFA_DPORT_SM_SCN:
		switch (dport->i2hmsg.scn.state) {
		case BFI_DPORT_SCN_DDPORT_DISABLED:
			bfa_sm_set_state(dport, bfa_dport_sm_disabled);
			dport->dynamic = BFA_FALSE;
			bfa_fcport_enable(dport->bfa);
			break;

		default:
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			bfa_sm_fault(dport->bfa, event);

		}
		break;

	case BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_OK);
		break;

	default:
		bfa_sm_fault(dport->bfa, event);
	}
}