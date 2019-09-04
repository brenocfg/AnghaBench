#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* def; int /*<<< orphan*/  speed; } ;
struct gem {int lstate; int timer_ticks; int /*<<< orphan*/  dev; TYPE_3__ phy_mii; int /*<<< orphan*/  last_forced_speed; } ;
struct TYPE_7__ {TYPE_1__* ops; int /*<<< orphan*/  magic_aneg; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* setup_forced ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  link ; 
#define  link_aneg 130 
 int link_force_ok ; 
#define  link_force_ret 129 
#define  link_force_try 128 
 int /*<<< orphan*/  netif_info (struct gem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_mdio_link_not_up(struct gem *gp)
{
	switch (gp->lstate) {
	case link_force_ret:
		netif_info(gp, link, gp->dev,
			   "Autoneg failed again, keeping forced mode\n");
		gp->phy_mii.def->ops->setup_forced(&gp->phy_mii,
			gp->last_forced_speed, DUPLEX_HALF);
		gp->timer_ticks = 5;
		gp->lstate = link_force_ok;
		return 0;
	case link_aneg:
		/* We try forced modes after a failed aneg only on PHYs that don't
		 * have "magic_aneg" bit set, which means they internally do the
		 * while forced-mode thingy. On these, we just restart aneg
		 */
		if (gp->phy_mii.def->magic_aneg)
			return 1;
		netif_info(gp, link, gp->dev, "switching to forced 100bt\n");
		/* Try forced modes. */
		gp->phy_mii.def->ops->setup_forced(&gp->phy_mii, SPEED_100,
			DUPLEX_HALF);
		gp->timer_ticks = 5;
		gp->lstate = link_force_try;
		return 0;
	case link_force_try:
		/* Downgrade from 100 to 10 Mbps if necessary.
		 * If already at 10Mbps, warn user about the
		 * situation every 10 ticks.
		 */
		if (gp->phy_mii.speed == SPEED_100) {
			gp->phy_mii.def->ops->setup_forced(&gp->phy_mii, SPEED_10,
				DUPLEX_HALF);
			gp->timer_ticks = 5;
			netif_info(gp, link, gp->dev,
				   "switching to forced 10bt\n");
			return 0;
		} else
			return 1;
	default:
		return 0;
	}
}