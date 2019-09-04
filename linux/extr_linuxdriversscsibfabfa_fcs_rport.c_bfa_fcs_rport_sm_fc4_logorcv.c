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
struct bfa_fcs_rport_s {int pwwn; int pid; int /*<<< orphan*/  fcs; int /*<<< orphan*/  prlo; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
#define  RPSM_EVENT_ADDRESS_CHANGE 135 
#define  RPSM_EVENT_DELETE 134 
#define  RPSM_EVENT_FC4_OFFLINE 133 
#define  RPSM_EVENT_HCB_ONLINE 132 
#define  RPSM_EVENT_LOGO_RCVD 131 
#define  RPSM_EVENT_PRLO_RCVD 130 
#define  RPSM_EVENT_SCN_OFFLINE 129 
#define  RPSM_EVENT_SCN_ONLINE 128 
 int /*<<< orphan*/  bfa_fcs_rport_hal_offline (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_logo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_prlo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_off_delete ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_hcb_logorcv ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_fc4_logorcv(struct bfa_fcs_rport_s *rport,
			enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_FC4_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_logorcv);
		bfa_fcs_rport_hal_offline(rport);
		break;

	case RPSM_EVENT_DELETE:
		if (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		if (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);

		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_off_delete);
		break;

	case RPSM_EVENT_SCN_ONLINE:
	case RPSM_EVENT_SCN_OFFLINE:
	case RPSM_EVENT_HCB_ONLINE:
	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
	case RPSM_EVENT_ADDRESS_CHANGE:
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}