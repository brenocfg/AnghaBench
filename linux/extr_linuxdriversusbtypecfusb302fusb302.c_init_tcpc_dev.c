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
struct tcpc_dev {int /*<<< orphan*/  pd_transmit; int /*<<< orphan*/  start_drp_toggling; int /*<<< orphan*/  set_roles; int /*<<< orphan*/  set_pd_rx; int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  set_vconn; int /*<<< orphan*/  set_polarity; int /*<<< orphan*/  get_cc; int /*<<< orphan*/  set_cc; int /*<<< orphan*/  get_current_limit; int /*<<< orphan*/  get_vbus; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcpm_get_cc ; 
 int /*<<< orphan*/  tcpm_get_current_limit ; 
 int /*<<< orphan*/  tcpm_get_vbus ; 
 int /*<<< orphan*/  tcpm_init ; 
 int /*<<< orphan*/  tcpm_pd_transmit ; 
 int /*<<< orphan*/  tcpm_set_cc ; 
 int /*<<< orphan*/  tcpm_set_pd_rx ; 
 int /*<<< orphan*/  tcpm_set_polarity ; 
 int /*<<< orphan*/  tcpm_set_roles ; 
 int /*<<< orphan*/  tcpm_set_vbus ; 
 int /*<<< orphan*/  tcpm_set_vconn ; 
 int /*<<< orphan*/  tcpm_start_drp_toggling ; 

__attribute__((used)) static void init_tcpc_dev(struct tcpc_dev *fusb302_tcpc_dev)
{
	fusb302_tcpc_dev->init = tcpm_init;
	fusb302_tcpc_dev->get_vbus = tcpm_get_vbus;
	fusb302_tcpc_dev->get_current_limit = tcpm_get_current_limit;
	fusb302_tcpc_dev->set_cc = tcpm_set_cc;
	fusb302_tcpc_dev->get_cc = tcpm_get_cc;
	fusb302_tcpc_dev->set_polarity = tcpm_set_polarity;
	fusb302_tcpc_dev->set_vconn = tcpm_set_vconn;
	fusb302_tcpc_dev->set_vbus = tcpm_set_vbus;
	fusb302_tcpc_dev->set_pd_rx = tcpm_set_pd_rx;
	fusb302_tcpc_dev->set_roles = tcpm_set_roles;
	fusb302_tcpc_dev->start_drp_toggling = tcpm_start_drp_toggling;
	fusb302_tcpc_dev->pd_transmit = tcpm_pd_transmit;
}