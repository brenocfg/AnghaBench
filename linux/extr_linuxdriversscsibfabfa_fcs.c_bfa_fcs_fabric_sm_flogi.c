#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pwwn; } ;
struct TYPE_6__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_3__* fcs; int /*<<< orphan*/  lps; int /*<<< orphan*/  bb_credit; int /*<<< orphan*/  fab_type; int /*<<< orphan*/  delay_timer; int /*<<< orphan*/  is_auth; int /*<<< orphan*/  auth_reqd; TYPE_2__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_7__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_N2N ; 
 int /*<<< orphan*/  BFA_FCS_FABRIC_RETRY_DELAY ; 
#define  BFA_FCS_FABRIC_SM_CONT_OP 133 
#define  BFA_FCS_FABRIC_SM_DELETE 132 
#define  BFA_FCS_FABRIC_SM_LINK_DOWN 131 
#define  BFA_FCS_FABRIC_SM_LOOPBACK 130 
#define  BFA_FCS_FABRIC_SM_NO_FABRIC 129 
#define  BFA_FCS_FABRIC_SM_RETRY_OP 128 
 int /*<<< orphan*/  BFA_FCS_FABRIC_SWITCHED ; 
 int /*<<< orphan*/  BFA_LPS_SM_OFFLINE ; 
 int /*<<< orphan*/  bfa_fcport_set_tx_bbcredit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_delay ; 
 int /*<<< orphan*/  bfa_fcs_fabric_delete (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_notify_online (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_set_opertype (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_auth ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_deleting ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_flogi_retry ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_linkdown ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_loopback ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_nofabric ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_online ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_flogi(struct bfa_fcs_fabric_s *fabric,
			enum bfa_fcs_fabric_event event)
{
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_CONT_OP:

		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		fabric->fab_type = BFA_FCS_FABRIC_SWITCHED;

		if (fabric->auth_reqd && fabric->is_auth) {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth);
			bfa_trc(fabric->fcs, event);
		} else {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_online);
			bfa_fcs_fabric_notify_online(fabric);
		}
		break;

	case BFA_FCS_FABRIC_SM_RETRY_OP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi_retry);
		bfa_timer_start(fabric->fcs->bfa, &fabric->delay_timer,
				bfa_fcs_fabric_delay, fabric,
				BFA_FCS_FABRIC_RETRY_DELAY);
		break;

	case BFA_FCS_FABRIC_SM_LOOPBACK:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_loopback);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_set_opertype(fabric);
		break;

	case BFA_FCS_FABRIC_SM_NO_FABRIC:
		fabric->fab_type = BFA_FCS_FABRIC_N2N;
		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		bfa_fcs_fabric_notify_online(fabric);
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_nofabric);
		break;

	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkdown);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		break;

	case BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_delete(fabric);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}