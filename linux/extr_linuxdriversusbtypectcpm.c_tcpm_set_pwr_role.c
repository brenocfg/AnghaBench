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
struct tcpm_port {int pwr_role; int /*<<< orphan*/  typec_port; int /*<<< orphan*/  data_role; TYPE_1__* tcpc; } ;
typedef  enum typec_role { ____Placeholder_typec_role } typec_role ;
struct TYPE_2__ {int (* set_roles ) (TYPE_1__*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_pwr_role (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcpm_set_pwr_role(struct tcpm_port *port, enum typec_role role)
{
	int ret;

	ret = port->tcpc->set_roles(port->tcpc, true, role,
				    port->data_role);
	if (ret < 0)
		return ret;

	port->pwr_role = role;
	typec_set_pwr_role(port->typec_port, role);

	return 0;
}