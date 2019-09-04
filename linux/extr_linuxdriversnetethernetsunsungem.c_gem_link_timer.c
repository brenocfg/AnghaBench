#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  advertising; TYPE_2__* def; int /*<<< orphan*/  speed; } ;
struct gem {scalar_t__ phy_type; scalar_t__ lstate; int timer_ticks; int /*<<< orphan*/  link_timer; TYPE_3__ phy_mii; int /*<<< orphan*/  last_forced_speed; scalar_t__ want_autoneg; scalar_t__ regs; scalar_t__ reset_task_pending; struct net_device* dev; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup_aneg ) (TYPE_3__*,int /*<<< orphan*/ ) ;scalar_t__ (* poll_link ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PCS_MIISTAT ; 
 int PCS_MIISTAT_LS ; 
 scalar_t__ found_mii_phy (struct gem*) ; 
 struct gem* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_begin_auto_negotiation (struct gem*,int /*<<< orphan*/ *) ; 
 int gem_mdio_link_not_up (struct gem*) ; 
 int /*<<< orphan*/  gem_schedule_reset (struct gem*) ; 
 scalar_t__ gem_set_link_modes (struct gem*) ; 
 struct gem* gp ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ link_down ; 
 scalar_t__ link_force_ret ; 
 scalar_t__ link_force_try ; 
 int /*<<< orphan*/  link_timer ; 
 scalar_t__ link_up ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct gem*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_msg_link (struct gem*) ; 
 scalar_t__ phy_serdes ; 
 scalar_t__ phy_serialink ; 
 int readl (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gem_link_timer(struct timer_list *t)
{
	struct gem *gp = from_timer(gp, t, link_timer);
	struct net_device *dev = gp->dev;
	int restart_aneg = 0;

	/* There's no point doing anything if we're going to be reset */
	if (gp->reset_task_pending)
		return;

	if (gp->phy_type == phy_serialink ||
	    gp->phy_type == phy_serdes) {
		u32 val = readl(gp->regs + PCS_MIISTAT);

		if (!(val & PCS_MIISTAT_LS))
			val = readl(gp->regs + PCS_MIISTAT);

		if ((val & PCS_MIISTAT_LS) != 0) {
			if (gp->lstate == link_up)
				goto restart;

			gp->lstate = link_up;
			netif_carrier_on(dev);
			(void)gem_set_link_modes(gp);
		}
		goto restart;
	}
	if (found_mii_phy(gp) && gp->phy_mii.def->ops->poll_link(&gp->phy_mii)) {
		/* Ok, here we got a link. If we had it due to a forced
		 * fallback, and we were configured for autoneg, we do
		 * retry a short autoneg pass. If you know your hub is
		 * broken, use ethtool ;)
		 */
		if (gp->lstate == link_force_try && gp->want_autoneg) {
			gp->lstate = link_force_ret;
			gp->last_forced_speed = gp->phy_mii.speed;
			gp->timer_ticks = 5;
			if (netif_msg_link(gp))
				netdev_info(dev,
					    "Got link after fallback, retrying autoneg once...\n");
			gp->phy_mii.def->ops->setup_aneg(&gp->phy_mii, gp->phy_mii.advertising);
		} else if (gp->lstate != link_up) {
			gp->lstate = link_up;
			netif_carrier_on(dev);
			if (gem_set_link_modes(gp))
				restart_aneg = 1;
		}
	} else {
		/* If the link was previously up, we restart the
		 * whole process
		 */
		if (gp->lstate == link_up) {
			gp->lstate = link_down;
			netif_info(gp, link, dev, "Link down\n");
			netif_carrier_off(dev);
			gem_schedule_reset(gp);
			/* The reset task will restart the timer */
			return;
		} else if (++gp->timer_ticks > 10) {
			if (found_mii_phy(gp))
				restart_aneg = gem_mdio_link_not_up(gp);
			else
				restart_aneg = 1;
		}
	}
	if (restart_aneg) {
		gem_begin_auto_negotiation(gp, NULL);
		return;
	}
restart:
	mod_timer(&gp->link_timer, jiffies + ((12 * HZ) / 10));
}