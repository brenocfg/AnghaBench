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
struct tcpm_port {int /*<<< orphan*/  vconn_role; int /*<<< orphan*/  typec_port; TYPE_1__* tcpc; } ;
struct TYPE_2__ {int (* set_vconn ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_SINK ; 
 int /*<<< orphan*/  TYPEC_SOURCE ; 
 int stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int) ; 
 int /*<<< orphan*/  typec_set_vconn_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_set_vconn(struct tcpm_port *port, bool enable)
{
	int ret;

	tcpm_log(port, "vconn:=%d", enable);

	ret = port->tcpc->set_vconn(port->tcpc, enable);
	if (!ret) {
		port->vconn_role = enable ? TYPEC_SOURCE : TYPEC_SINK;
		typec_set_vconn_role(port->typec_port, port->vconn_role);
	}

	return ret;
}