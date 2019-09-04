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
struct phylink {scalar_t__ link_an_mode; int /*<<< orphan*/  link_poll; int /*<<< orphan*/  link_gpio; scalar_t__ sfp_bus; scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MLO_AN_FIXED ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  phylink_run_resolve_and_disable (struct phylink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_upstream_stop (scalar_t__) ; 

void phylink_stop(struct phylink *pl)
{
	ASSERT_RTNL();

	if (pl->phydev)
		phy_stop(pl->phydev);
	if (pl->sfp_bus)
		sfp_upstream_stop(pl->sfp_bus);
	if (pl->link_an_mode == MLO_AN_FIXED && !IS_ERR(pl->link_gpio))
		del_timer_sync(&pl->link_poll);

	phylink_run_resolve_and_disable(pl, PHYLINK_DISABLE_STOPPED);
}