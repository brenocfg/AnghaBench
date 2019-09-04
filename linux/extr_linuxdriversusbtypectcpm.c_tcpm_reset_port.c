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
struct TYPE_3__ {int supported; } ;
struct tcpm_port {int attached; int pd_capable; int rx_msgid; int /*<<< orphan*/  psy; int /*<<< orphan*/  usb_type; scalar_t__ try_snk_count; scalar_t__ try_src_count; TYPE_2__* tcpc; TYPE_1__ pps_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_pd_rx ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_USB_TYPE_C ; 
 int /*<<< orphan*/  TYPEC_ORIENTATION_NONE ; 
 int /*<<< orphan*/  TYPEC_POLARITY_CC1 ; 
 int /*<<< orphan*/  TYPEC_STATE_SAFE ; 
 int /*<<< orphan*/  USB_ROLE_NONE ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tcpm_init_vbus (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_init_vconn (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_mux_set (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_attached_state (struct tcpm_port*,int) ; 
 int /*<<< orphan*/  tcpm_set_current_limit (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_polarity (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_typec_disconnect (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_unregister_altmodes (struct tcpm_port*) ; 

__attribute__((used)) static void tcpm_reset_port(struct tcpm_port *port)
{
	tcpm_unregister_altmodes(port);
	tcpm_typec_disconnect(port);
	port->attached = false;
	port->pd_capable = false;
	port->pps_data.supported = false;

	/*
	 * First Rx ID should be 0; set this to a sentinel of -1 so that
	 * we can check tcpm_pd_rx_handler() if we had seen it before.
	 */
	port->rx_msgid = -1;

	port->tcpc->set_pd_rx(port->tcpc, false);
	tcpm_init_vbus(port);	/* also disables charging */
	tcpm_init_vconn(port);
	tcpm_set_current_limit(port, 0, 0);
	tcpm_set_polarity(port, TYPEC_POLARITY_CC1);
	tcpm_mux_set(port, TYPEC_STATE_SAFE, USB_ROLE_NONE,
		     TYPEC_ORIENTATION_NONE);
	tcpm_set_attached_state(port, false);
	port->try_src_count = 0;
	port->try_snk_count = 0;
	port->usb_type = POWER_SUPPLY_USB_TYPE_C;

	power_supply_changed(port->psy);
}