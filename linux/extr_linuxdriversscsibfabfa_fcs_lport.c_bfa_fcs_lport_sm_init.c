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
struct TYPE_4__ {int pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; TYPE_1__* fabric; int /*<<< orphan*/  vport; TYPE_2__ port_cfg; } ;
typedef  enum bfa_fcs_lport_event { ____Placeholder_bfa_fcs_lport_event } bfa_fcs_lport_event ;
struct TYPE_3__ {int /*<<< orphan*/  stop_wc; } ;

/* Variables and functions */
#define  BFA_FCS_PORT_SM_DELETE 131 
#define  BFA_FCS_PORT_SM_OFFLINE 130 
#define  BFA_FCS_PORT_SM_ONLINE 129 
#define  BFA_FCS_PORT_SM_STOP 128 
 int /*<<< orphan*/  bfa_fcs_lport_deleted (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_online_actions (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_lport_sm_uninit ; 
 int /*<<< orphan*/  bfa_fcs_vport_stop_comp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_lport_sm_init(struct bfa_fcs_lport_s *port,
			enum bfa_fcs_lport_event event)
{
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	switch (event) {
	case BFA_FCS_PORT_SM_ONLINE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_online);
		bfa_fcs_lport_online_actions(port);
		break;

	case BFA_FCS_PORT_SM_DELETE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_uninit);
		bfa_fcs_lport_deleted(port);
		break;

	case BFA_FCS_PORT_SM_STOP:
		/* If vport - send completion call back */
		if (port->vport)
			bfa_fcs_vport_stop_comp(port->vport);
		else
			bfa_wc_down(&(port->fabric->stop_wc));
		break;

	case BFA_FCS_PORT_SM_OFFLINE:
		break;

	default:
		bfa_sm_fault(port->fcs, event);
	}
}