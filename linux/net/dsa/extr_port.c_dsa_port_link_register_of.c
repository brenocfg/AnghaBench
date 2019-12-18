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
struct dsa_switch {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  dn; struct dsa_switch* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  adjust_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dsa_port_fixed_link_register_of (struct dsa_port*) ; 
 int dsa_port_phylink_register (struct dsa_port*) ; 
 int dsa_port_setup_phy_of (struct dsa_port*,int) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 

int dsa_port_link_register_of(struct dsa_port *dp)
{
	struct dsa_switch *ds = dp->ds;

	if (!ds->ops->adjust_link)
		return dsa_port_phylink_register(dp);

	dev_warn(ds->dev,
		 "Using legacy PHYLIB callbacks. Please migrate to PHYLINK!\n");

	if (of_phy_is_fixed_link(dp->dn))
		return dsa_port_fixed_link_register_of(dp);
	else
		return dsa_port_setup_phy_of(dp, true);
}