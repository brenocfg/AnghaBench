#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;
struct tcpm_port {unsigned int operating_snk_mw; int update_sink_caps; int state; int /*<<< orphan*/  lock; TYPE_1__ pps_data; int /*<<< orphan*/  snk_pdo; int /*<<< orphan*/  nr_snk_pdo; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNK_NEGOTIATE_CAPABILITIES 132 
#define  SNK_NEGOTIATE_PPS_CAPABILITIES 131 
#define  SNK_READY 130 
#define  SNK_TRANSITION_SINK 129 
#define  SNK_TRANSITION_SINK_VBUS 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_copy_pdos (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ tcpm_validate_caps (struct tcpm_port*,int /*<<< orphan*/  const*,unsigned int) ; 

int tcpm_update_sink_capabilities(struct tcpm_port *port, const u32 *pdo,
				  unsigned int nr_pdo,
				  unsigned int operating_snk_mw)
{
	if (tcpm_validate_caps(port, pdo, nr_pdo))
		return -EINVAL;

	mutex_lock(&port->lock);
	port->nr_snk_pdo = tcpm_copy_pdos(port->snk_pdo, pdo, nr_pdo);
	port->operating_snk_mw = operating_snk_mw;
	port->update_sink_caps = true;

	switch (port->state) {
	case SNK_NEGOTIATE_CAPABILITIES:
	case SNK_NEGOTIATE_PPS_CAPABILITIES:
	case SNK_READY:
	case SNK_TRANSITION_SINK:
	case SNK_TRANSITION_SINK_VBUS:
		if (port->pps_data.active)
			tcpm_set_state(port, SNK_NEGOTIATE_PPS_CAPABILITIES, 0);
		else
			tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
		break;
	default:
		break;
	}
	mutex_unlock(&port->lock);
	return 0;
}