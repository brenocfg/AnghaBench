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
struct TYPE_3__ {int /*<<< orphan*/  interface; } ;
struct phylink {scalar_t__ link_an_mode; scalar_t__ phydev; scalar_t__ sfp_bus; int /*<<< orphan*/  link_poll; int /*<<< orphan*/  link_gpio; int /*<<< orphan*/  phylink_disable_state; TYPE_1__ link_config; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MLO_AN_FIXED ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 
 int /*<<< orphan*/  phylink_an_mode_str (scalar_t__) ; 
 int /*<<< orphan*/  phylink_mac_an_restart (struct phylink*) ; 
 int /*<<< orphan*/  phylink_mac_config (struct phylink*,TYPE_1__*) ; 
 int /*<<< orphan*/  phylink_resolve_flow (struct phylink*,TYPE_1__*) ; 
 int /*<<< orphan*/  phylink_run_resolve (struct phylink*) ; 
 int /*<<< orphan*/  sfp_upstream_start (scalar_t__) ; 

void phylink_start(struct phylink *pl)
{
	ASSERT_RTNL();

	netdev_info(pl->netdev, "configuring for %s/%s link mode\n",
		    phylink_an_mode_str(pl->link_an_mode),
		    phy_modes(pl->link_config.interface));

	/* Always set the carrier off */
	netif_carrier_off(pl->netdev);

	/* Apply the link configuration to the MAC when starting. This allows
	 * a fixed-link to start with the correct parameters, and also
	 * ensures that we set the appropriate advertisement for Serdes links.
	 */
	phylink_resolve_flow(pl, &pl->link_config);
	phylink_mac_config(pl, &pl->link_config);

	/* Restart autonegotiation if using 802.3z to ensure that the link
	 * parameters are properly negotiated.  This is necessary for DSA
	 * switches using 802.3z negotiation to ensure they see our modes.
	 */
	phylink_mac_an_restart(pl);

	clear_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state);
	phylink_run_resolve(pl);

	if (pl->link_an_mode == MLO_AN_FIXED && !IS_ERR(pl->link_gpio))
		mod_timer(&pl->link_poll, jiffies + HZ);
	if (pl->sfp_bus)
		sfp_upstream_start(pl->sfp_bus);
	if (pl->phydev)
		phy_start(pl->phydev);
}