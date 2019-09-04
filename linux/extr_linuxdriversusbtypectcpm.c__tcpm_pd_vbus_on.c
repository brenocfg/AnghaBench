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
struct tcpm_port {int vbus_present; int state; int explicit_contract; } ;

/* Variables and functions */
 int const SNK_ATTACHED ; 
#define  SNK_DEBOUNCED 142 
#define  SNK_DISCOVERY 141 
 int const SNK_HARD_RESET_SINK_ON ; 
#define  SNK_HARD_RESET_WAIT_VBUS 140 
 int const SNK_READY ; 
#define  SNK_TRANSITION_SINK_VBUS 139 
#define  SNK_TRY 138 
#define  SNK_TRYWAIT 137 
#define  SNK_TRYWAIT_DEBOUNCE 136 
#define  SNK_TRYWAIT_VBUS 135 
#define  SNK_TRY_WAIT_DEBOUNCE 134 
#define  SRC_ATTACHED 133 
#define  SRC_HARD_RESET_VBUS_ON 132 
 int const SRC_STARTUP ; 
 int const SRC_TRY ; 
#define  SRC_TRYWAIT 131 
#define  SRC_TRYWAIT_DEBOUNCE 130 
#define  SRC_TRY_DEBOUNCE 129 
#define  SRC_TRY_WAIT 128 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*) ; 
 int /*<<< orphan*/  tcpm_port_is_sink (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_try_src (struct tcpm_port*) ; 

__attribute__((used)) static void _tcpm_pd_vbus_on(struct tcpm_port *port)
{
	tcpm_log_force(port, "VBUS on");
	port->vbus_present = true;
	switch (port->state) {
	case SNK_TRANSITION_SINK_VBUS:
		port->explicit_contract = true;
		tcpm_set_state(port, SNK_READY, 0);
		break;
	case SNK_DISCOVERY:
		tcpm_set_state(port, SNK_DISCOVERY, 0);
		break;

	case SNK_DEBOUNCED:
		tcpm_set_state(port, tcpm_try_src(port) ? SRC_TRY
							: SNK_ATTACHED,
				       0);
		break;
	case SNK_HARD_RESET_WAIT_VBUS:
		tcpm_set_state(port, SNK_HARD_RESET_SINK_ON, 0);
		break;
	case SRC_ATTACHED:
		tcpm_set_state(port, SRC_STARTUP, 0);
		break;
	case SRC_HARD_RESET_VBUS_ON:
		tcpm_set_state(port, SRC_STARTUP, 0);
		break;

	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;
	case SRC_TRYWAIT:
		/* Do nothing, Waiting for Rd to be detected */
		break;
	case SRC_TRYWAIT_DEBOUNCE:
		tcpm_set_state(port, SRC_TRYWAIT, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, waiting for PD_DEBOUNCE to do be done */
		break;
	case SNK_TRYWAIT:
		/* Do nothing, waiting for tCCDebounce */
		break;
	case SNK_TRYWAIT_VBUS:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACHED, 0);
		break;
	case SNK_TRYWAIT_DEBOUNCE:
		/* Do nothing, waiting for Rp */
		break;
	case SRC_TRY_WAIT:
	case SRC_TRY_DEBOUNCE:
		/* Do nothing, waiting for sink detection */
		break;
	default:
		break;
	}
}