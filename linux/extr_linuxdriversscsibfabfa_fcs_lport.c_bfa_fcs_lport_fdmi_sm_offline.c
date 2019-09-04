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
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; int /*<<< orphan*/  vport; TYPE_2__ port_cfg; } ;
struct bfa_fcs_lport_fdmi_s {scalar_t__ retry_cnt; TYPE_1__* ms; } ;
typedef  enum port_fdmi_event { ____Placeholder_port_fdmi_event } port_fdmi_event ;
struct TYPE_3__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
#define  FDMISM_EVENT_PORT_OFFLINE 129 
#define  FDMISM_EVENT_PORT_ONLINE 128 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_send_rhba (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_send_rprt (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_sending_rhba ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_sending_rprt ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_fdmi_sm_offline(struct bfa_fcs_lport_fdmi_s *fdmi,
			     enum port_fdmi_event event)
{
	struct bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	fdmi->retry_cnt = 0;

	switch (event) {
	case FDMISM_EVENT_PORT_ONLINE:
		if (port->vport) {
			/*
			 * For Vports, register a new port.
			 */
			bfa_sm_set_state(fdmi,
					 bfa_fcs_lport_fdmi_sm_sending_rprt);
			bfa_fcs_lport_fdmi_send_rprt(fdmi, NULL);
		} else {
			/*
			 * For a base port, we should first register the HBA
			 * attribute. The HBA attribute also contains the base
			 *  port registration.
			 */
			bfa_sm_set_state(fdmi,
					 bfa_fcs_lport_fdmi_sm_sending_rhba);
			bfa_fcs_lport_fdmi_send_rhba(fdmi, NULL);
		}
		break;

	case FDMISM_EVENT_PORT_OFFLINE:
		break;

	default:
		bfa_sm_fault(port->fcs, event);
	}
}