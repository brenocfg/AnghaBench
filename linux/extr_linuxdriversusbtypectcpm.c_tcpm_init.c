#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcpm_port {int vbus_never_low; TYPE_1__* tcpc; scalar_t__ vbus_present; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
struct TYPE_4__ {scalar_t__ (* get_cc ) (TYPE_1__*,int*,int*) ;scalar_t__ (* get_vbus ) (TYPE_1__*) ;int /*<<< orphan*/  (* init ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_RESET ; 
 int /*<<< orphan*/  _tcpm_cc_change (struct tcpm_port*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 
 scalar_t__ stub3 (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  tcpm_default_state (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_reset_port (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcpm_init(struct tcpm_port *port)
{
	enum typec_cc_status cc1, cc2;

	port->tcpc->init(port->tcpc);

	tcpm_reset_port(port);

	/*
	 * XXX
	 * Should possibly wait for VBUS to settle if it was enabled locally
	 * since tcpm_reset_port() will disable VBUS.
	 */
	port->vbus_present = port->tcpc->get_vbus(port->tcpc);
	if (port->vbus_present)
		port->vbus_never_low = true;

	tcpm_set_state(port, tcpm_default_state(port), 0);

	if (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
		_tcpm_cc_change(port, cc1, cc2);

	/*
	 * Some adapters need a clean slate at startup, and won't recover
	 * otherwise. So do not try to be fancy and force a clean disconnect.
	 */
	tcpm_set_state(port, PORT_RESET, 0);
}