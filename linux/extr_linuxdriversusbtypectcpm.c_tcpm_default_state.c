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
struct tcpm_port {scalar_t__ port_type; scalar_t__ try_role; TYPE_2__* tcpc; } ;
typedef  enum tcpm_state { ____Placeholder_tcpm_state } tcpm_state ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {scalar_t__ default_role; } ;

/* Variables and functions */
 int SNK_UNATTACHED ; 
 int SRC_UNATTACHED ; 
 scalar_t__ TYPEC_PORT_DRP ; 
 scalar_t__ TYPEC_PORT_SNK ; 
 scalar_t__ TYPEC_SINK ; 
 scalar_t__ TYPEC_SOURCE ; 

__attribute__((used)) static enum tcpm_state tcpm_default_state(struct tcpm_port *port)
{
	if (port->port_type == TYPEC_PORT_DRP) {
		if (port->try_role == TYPEC_SINK)
			return SNK_UNATTACHED;
		else if (port->try_role == TYPEC_SOURCE)
			return SRC_UNATTACHED;
		else if (port->tcpc->config->default_role == TYPEC_SINK)
			return SNK_UNATTACHED;
		/* Fall through to return SRC_UNATTACHED */
	} else if (port->port_type == TYPEC_PORT_SNK) {
		return SNK_UNATTACHED;
	}
	return SRC_UNATTACHED;
}