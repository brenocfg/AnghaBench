#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_rport_s {int pwwn; int pid; TYPE_1__* fcs; int /*<<< orphan*/  prlo; int /*<<< orphan*/  timer; int /*<<< orphan*/  plogi_retries; int /*<<< orphan*/  ns_retries; TYPE_3__* port; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;
struct TYPE_5__ {int /*<<< orphan*/  fabric; } ;
struct TYPE_4__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (int) ; 
 int /*<<< orphan*/  BFA_TRUE ; 
#define  RPSM_EVENT_ADDRESS_CHANGE 135 
#define  RPSM_EVENT_DELETE 134 
#define  RPSM_EVENT_HCB_OFFLINE 133 
#define  RPSM_EVENT_LOGO_IMP 132 
#define  RPSM_EVENT_LOGO_RCVD 131 
#define  RPSM_EVENT_PRLO_RCVD 130 
#define  RPSM_EVENT_SCN_OFFLINE 129 
#define  RPSM_EVENT_SCN_ONLINE 128 
 int /*<<< orphan*/  bfa_fcs_fabric_is_switched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_is_online (TYPE_3__*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_del_timeout ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_logo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_nsdisc (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_plogi (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_prlo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_delete_pending ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_hcb_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_nsdisc_sending ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_plogi_sending ; 
 int /*<<< orphan*/  bfa_fcs_rport_timeout ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_hcb_logorcv(struct bfa_fcs_rport_s *rport,
			enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_HCB_OFFLINE:
	case RPSM_EVENT_ADDRESS_CHANGE:
		if (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		if (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);
		/*
		 * If the lport is online and if the rport is not a well
		 * known address port,
		 * we try to re-discover the r-port.
		 */
		if (bfa_fcs_lport_is_online(rport->port) &&
			(!BFA_FCS_PID_IS_WKA(rport->pid))) {
			if (bfa_fcs_fabric_is_switched(rport->port->fabric)) {
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_nsdisc_sending);
				rport->ns_retries = 0;
				bfa_fcs_rport_send_nsdisc(rport, NULL);
			} else {
				/* For N2N  Direct Attach, try to re-login */
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_plogi_sending);
				rport->plogi_retries = 0;
				bfa_fcs_rport_send_plogi(rport, NULL);
			}
		} else {
			/*
			 * if it is not a well known address, reset the
			 * pid to 0.
			 */
			if (!BFA_FCS_PID_IS_WKA(rport->pid))
				rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_timer_start(rport->fcs->bfa, &rport->timer,
					bfa_fcs_rport_timeout, rport,
					bfa_fcs_rport_del_timeout);
		}
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_delete_pending);
		if (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		if (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);
		break;

	case RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_offline);
		break;

	case RPSM_EVENT_SCN_ONLINE:
	case RPSM_EVENT_SCN_OFFLINE:
	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		/*
		 * Ignore - already processing a LOGO.
		 */
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}