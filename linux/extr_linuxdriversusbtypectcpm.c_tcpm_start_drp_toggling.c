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
struct tcpm_port {scalar_t__ port_type; TYPE_1__* tcpc; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
struct TYPE_2__ {int (* start_drp_toggling ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 scalar_t__ TYPEC_PORT_DRP ; 
 int stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*) ; 

__attribute__((used)) static bool tcpm_start_drp_toggling(struct tcpm_port *port,
				    enum typec_cc_status cc)
{
	int ret;

	if (port->tcpc->start_drp_toggling &&
	    port->port_type == TYPEC_PORT_DRP) {
		tcpm_log_force(port, "Start DRP toggling");
		ret = port->tcpc->start_drp_toggling(port->tcpc, cc);
		if (!ret)
			return true;
	}

	return false;
}