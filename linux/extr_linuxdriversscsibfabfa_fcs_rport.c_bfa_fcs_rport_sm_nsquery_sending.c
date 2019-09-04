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
struct bfa_fcs_rport_s {int pwwn; int pid; TYPE_1__* fcs; int /*<<< orphan*/  fcxp_wqe; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;
struct TYPE_3__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
#define  RPSM_EVENT_ADDRESS_CHANGE 136 
#define  RPSM_EVENT_DELETE 135 
#define  RPSM_EVENT_FAB_SCN 134 
#define  RPSM_EVENT_FCXP_SENT 133 
#define  RPSM_EVENT_LOGO_IMP 132 
#define  RPSM_EVENT_LOGO_RCVD 131 
#define  RPSM_EVENT_PLOGI_COMP 130 
#define  RPSM_EVENT_PLOGI_RCVD 129 
#define  RPSM_EVENT_PRLO_RCVD 128 
 int /*<<< orphan*/  bfa_fcs_rport_hal_offline_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logorcv ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logosend ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_nsquery ; 
 int /*<<< orphan*/  bfa_fcxp_walloc_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_nsquery_sending(struct bfa_fcs_rport_s *rport,
	 enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsquery);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_FAB_SCN:
		/*
		 * ignore SCN, wait for response to query itself
		 */
		break;

	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_LOGO_IMP:
	case RPSM_EVENT_PLOGI_RCVD:
	case RPSM_EVENT_ADDRESS_CHANGE:
	case RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}