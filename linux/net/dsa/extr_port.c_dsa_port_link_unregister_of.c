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
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  dn; int /*<<< orphan*/  pl; struct dsa_switch* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  adjust_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_port_setup_phy_of (struct dsa_port*,int) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void dsa_port_link_unregister_of(struct dsa_port *dp)
{
	struct dsa_switch *ds = dp->ds;

	if (!ds->ops->adjust_link) {
		rtnl_lock();
		phylink_disconnect_phy(dp->pl);
		rtnl_unlock();
		phylink_destroy(dp->pl);
		return;
	}

	if (of_phy_is_fixed_link(dp->dn))
		of_phy_deregister_fixed_link(dp->dn);
	else
		dsa_port_setup_phy_of(dp, false);
}