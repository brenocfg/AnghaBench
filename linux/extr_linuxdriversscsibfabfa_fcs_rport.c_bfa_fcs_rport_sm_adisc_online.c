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
struct bfa_fcs_rport_s {int pwwn; int pid; int /*<<< orphan*/  fcs; int /*<<< orphan*/  fcxp; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;

/* Variables and functions */
#define  RPSM_EVENT_ACCEPTED 136 
#define  RPSM_EVENT_ADDRESS_CHANGE 135 
#define  RPSM_EVENT_DELETE 134 
#define  RPSM_EVENT_FAB_SCN 133 
#define  RPSM_EVENT_FAILED 132 
#define  RPSM_EVENT_LOGO_IMP 131 
#define  RPSM_EVENT_LOGO_RCVD 130 
#define  RPSM_EVENT_PLOGI_RCVD 129 
#define  RPSM_EVENT_PRLO_RCVD 128 
 int /*<<< orphan*/  bfa_fcs_rport_hal_offline_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logorcv ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logosend ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_online ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_adisc_online(struct bfa_fcs_rport_s *rport,
				enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
		break;

	case RPSM_EVENT_PLOGI_RCVD:
		/*
		 * Too complex to cleanup FC-4 & rport and then acc to PLOGI.
		 * At least go offline when a PLOGI is received.
		 */
		bfa_fcxp_discard(rport->fcxp);
		/*
		 * !!! fall through !!!
		 */

	case RPSM_EVENT_FAILED:
	case RPSM_EVENT_ADDRESS_CHANGE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_FAB_SCN:
		/*
		 * already processing RSCN
		 */
		break;

	case RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}