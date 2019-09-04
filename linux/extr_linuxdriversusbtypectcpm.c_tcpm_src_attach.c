#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcpm_port {scalar_t__ cc2; int attached; scalar_t__ cc1; int pd_capable; int send_discover; TYPE_1__* tcpc; int /*<<< orphan*/ * partner; } ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;
struct TYPE_3__ {int (* set_pd_rx ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 scalar_t__ TYPEC_CC_RA ; 
 scalar_t__ TYPEC_CC_RD ; 
 int /*<<< orphan*/  TYPEC_HOST ; 
 int /*<<< orphan*/  TYPEC_ORIENTATION_NONE ; 
 int TYPEC_POLARITY_CC1 ; 
 int TYPEC_POLARITY_CC2 ; 
 int /*<<< orphan*/  TYPEC_SOURCE ; 
 int /*<<< orphan*/  TYPEC_STATE_SAFE ; 
 int /*<<< orphan*/  USB_ROLE_NONE ; 
 int stub1 (TYPE_1__*,int) ; 
 int stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tcpm_mux_set (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcpm_set_polarity (struct tcpm_port*,int) ; 
 int tcpm_set_roles (struct tcpm_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcpm_set_vbus (struct tcpm_port*,int) ; 
 int tcpm_set_vconn (struct tcpm_port*,int) ; 

__attribute__((used)) static int tcpm_src_attach(struct tcpm_port *port)
{
	enum typec_cc_polarity polarity =
				port->cc2 == TYPEC_CC_RD ? TYPEC_POLARITY_CC2
							 : TYPEC_POLARITY_CC1;
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_polarity(port, polarity);
	if (ret < 0)
		return ret;

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE, TYPEC_HOST);
	if (ret < 0)
		return ret;

	ret = port->tcpc->set_pd_rx(port->tcpc, true);
	if (ret < 0)
		goto out_disable_mux;

	/*
	 * USB Type-C specification, version 1.2,
	 * chapter 4.5.2.2.8.1 (Attached.SRC Requirements)
	 * Enable VCONN only if the non-RD port is set to RA.
	 */
	if ((polarity == TYPEC_POLARITY_CC1 && port->cc2 == TYPEC_CC_RA) ||
	    (polarity == TYPEC_POLARITY_CC2 && port->cc1 == TYPEC_CC_RA)) {
		ret = tcpm_set_vconn(port, true);
		if (ret < 0)
			goto out_disable_pd;
	}

	ret = tcpm_set_vbus(port, true);
	if (ret < 0)
		goto out_disable_vconn;

	port->pd_capable = false;

	port->partner = NULL;

	port->attached = true;
	port->send_discover = true;

	return 0;

out_disable_vconn:
	tcpm_set_vconn(port, false);
out_disable_pd:
	port->tcpc->set_pd_rx(port->tcpc, false);
out_disable_mux:
	tcpm_mux_set(port, TYPEC_STATE_SAFE, USB_ROLE_NONE,
		     TYPEC_ORIENTATION_NONE);
	return ret;
}