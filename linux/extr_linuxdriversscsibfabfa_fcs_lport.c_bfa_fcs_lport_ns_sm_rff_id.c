#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_lport_ns_s {TYPE_3__* port; int /*<<< orphan*/  fcxp; int /*<<< orphan*/  timer; } ;
typedef  enum vport_ns_event { ____Placeholder_vport_ns_event } vport_ns_event ;
struct TYPE_8__ {int /*<<< orphan*/  ns_retries; } ;
struct TYPE_7__ {int pwwn; } ;
struct TYPE_9__ {int /*<<< orphan*/  fcs; TYPE_2__ stats; TYPE_1__ port_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_GET_HAL_FROM_PORT (TYPE_3__*) ; 
 int /*<<< orphan*/  BFA_FCS_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  BFA_FCS_VPORT_IS_INITIATOR_MODE (TYPE_3__*) ; 
#define  NSSM_EVENT_PORT_OFFLINE 130 
#define  NSSM_EVENT_RSP_ERROR 129 
#define  NSSM_EVENT_RSP_OK 128 
 int /*<<< orphan*/  __fcs_min_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ms_online (TYPE_3__*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_boot_target_disc (TYPE_3__*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_send_gid_ft (struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_sm_rff_id_retry ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_sm_sending_gid_ft ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_timeout ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_ns_sm_rff_id(struct bfa_fcs_lport_ns_s *ns,
			enum vport_ns_event event)
{
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	switch (event) {
	case NSSM_EVENT_RSP_OK:

		/*
		 * If min cfg mode is enabled, we donot initiate rport
		 * discovery with the fabric. Instead, we will retrieve the
		 * boot targets from HAL/FW.
		 */
		if (__fcs_min_cfg(ns->port->fcs)) {
			bfa_fcs_lport_ns_boot_target_disc(ns->port);
			bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_online);
			return;
		}

		/*
		 * If the port role is Initiator Mode issue NS query.
		 * If it is Target Mode, skip this and go to online.
		 */
		if (BFA_FCS_VPORT_IS_INITIATOR_MODE(ns->port)) {
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_gid_ft);
			bfa_fcs_lport_ns_send_gid_ft(ns, NULL);
		}
		/*
		 * kick off mgmt srvr state machine
		 */
		bfa_fcs_lport_ms_online(ns->port);
		break;

	case NSSM_EVENT_RSP_ERROR:
		/*
		 * Start timer for a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rff_id_retry);
		ns->port->stats.ns_retries++;
		bfa_timer_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->timer, bfa_fcs_lport_ns_timeout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		break;

	case NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		break;

	default:
		bfa_sm_fault(ns->port->fcs, event);
	}
}