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
struct TYPE_3__ {int pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; TYPE_2__* fabric; int /*<<< orphan*/  vport; int /*<<< orphan*/  num_rports; TYPE_1__ port_cfg; } ;
typedef  enum bfa_fcs_lport_event { ____Placeholder_bfa_fcs_lport_event } bfa_fcs_lport_event ;
struct TYPE_4__ {int /*<<< orphan*/  stop_wc; } ;

/* Variables and functions */
#define  BFA_FCS_PORT_SM_DELRPORT 128 
 int /*<<< orphan*/  bfa_fcs_lport_sm_init ; 
 int /*<<< orphan*/  bfa_fcs_vport_stop_comp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_lport_sm_stopping(struct bfa_fcs_lport_s *port,
			  enum bfa_fcs_lport_event event)
{
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	switch (event) {
	case BFA_FCS_PORT_SM_DELRPORT:
		if (port->num_rports == 0) {
			bfa_sm_set_state(port, bfa_fcs_lport_sm_init);
			/* If vport - send completion call back */
			if (port->vport)
				bfa_fcs_vport_stop_comp(port->vport);
			else
				bfa_wc_down(&(port->fabric->stop_wc));
		}
		break;

	default:
		bfa_sm_fault(port->fcs, event);
	}
}