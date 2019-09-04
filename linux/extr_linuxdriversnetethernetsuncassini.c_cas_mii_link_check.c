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
typedef  int u16 ;
struct cas {scalar_t__ lstate; int link_cntl; int link_fcntl; int timer_ticks; int /*<<< orphan*/  dev; scalar_t__ opened; int /*<<< orphan*/  link_transition; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int const BMSR_LSTATUS ; 
 int /*<<< orphan*/  LINK_TRANSITION_LINK_CONFIG ; 
 int /*<<< orphan*/  LINK_TRANSITION_LINK_DOWN ; 
 int /*<<< orphan*/  LINK_TRANSITION_LINK_UP ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  cas_mdio_link_not_up (struct cas*) ; 
 int /*<<< orphan*/  cas_mif_poll (struct cas*,int) ; 
 int cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_phy_write (struct cas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cas_set_link_modes (struct cas*) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ link_down ; 
 scalar_t__ link_force_ret ; 
 scalar_t__ link_force_try ; 
 scalar_t__ link_up ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cas_mii_link_check(struct cas *cp, const u16 bmsr)
{
	int restart;

	if (bmsr & BMSR_LSTATUS) {
		/* Ok, here we got a link. If we had it due to a forced
		 * fallback, and we were configured for autoneg, we
		 * retry a short autoneg pass. If you know your hub is
		 * broken, use ethtool ;)
		 */
		if ((cp->lstate == link_force_try) &&
		    (cp->link_cntl & BMCR_ANENABLE)) {
			cp->lstate = link_force_ret;
			cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
			cas_mif_poll(cp, 0);
			cp->link_fcntl = cas_phy_read(cp, MII_BMCR);
			cp->timer_ticks = 5;
			if (cp->opened)
				netif_info(cp, link, cp->dev,
					   "Got link after fallback, retrying autoneg once...\n");
			cas_phy_write(cp, MII_BMCR,
				      cp->link_fcntl | BMCR_ANENABLE |
				      BMCR_ANRESTART);
			cas_mif_poll(cp, 1);

		} else if (cp->lstate != link_up) {
			cp->lstate = link_up;
			cp->link_transition = LINK_TRANSITION_LINK_UP;

			if (cp->opened) {
				cas_set_link_modes(cp);
				netif_carrier_on(cp->dev);
			}
		}
		return 0;
	}

	/* link not up. if the link was previously up, we restart the
	 * whole process
	 */
	restart = 0;
	if (cp->lstate == link_up) {
		cp->lstate = link_down;
		cp->link_transition = LINK_TRANSITION_LINK_DOWN;

		netif_carrier_off(cp->dev);
		if (cp->opened)
			netif_info(cp, link, cp->dev, "Link down\n");
		restart = 1;

	} else if (++cp->timer_ticks > 10)
		cas_mdio_link_not_up(cp);

	return restart;
}