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
struct bfa_fcs_lport_ms_s {TYPE_2__* port; int /*<<< orphan*/  fcxp_wqe; } ;
typedef  enum port_ms_event { ____Placeholder_port_ms_event } port_ms_event ;
struct TYPE_3__ {int pwwn; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcs; TYPE_1__ port_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_GET_HAL_FROM_PORT (TYPE_2__*) ; 
#define  MSSM_EVENT_FCXP_SENT 129 
#define  MSSM_EVENT_PORT_OFFLINE 128 
 int /*<<< orphan*/  bfa_fcs_lport_ms_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_lport_ms_sm_plogi ; 
 int /*<<< orphan*/  bfa_fcxp_walloc_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_ms_sm_plogi_sending(struct bfa_fcs_lport_ms_s *ms,
				enum port_ms_event event)
{
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	switch (event) {
	case MSSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_plogi);
		break;

	case MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
					   &ms->fcxp_wqe);
		break;

	default:
		bfa_sm_fault(ms->port->fcs, event);
	}
}