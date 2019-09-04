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
struct tcpm_port {int vbus_source; int vbus_charge; TYPE_1__* tcpc; } ;
struct TYPE_2__ {int (* set_vbus ) (TYPE_1__*,int,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int,int) ; 

__attribute__((used)) static int tcpm_init_vbus(struct tcpm_port *port)
{
	int ret;

	ret = port->tcpc->set_vbus(port->tcpc, false, false);
	port->vbus_source = false;
	port->vbus_charge = false;
	return ret;
}