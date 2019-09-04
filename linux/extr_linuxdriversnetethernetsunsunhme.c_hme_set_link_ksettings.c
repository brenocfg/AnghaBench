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
struct net_device {int dummy; } ;
struct happy_meal {int /*<<< orphan*/  happy_lock; int /*<<< orphan*/  tcvregs; int /*<<< orphan*/  happy_timer; } ;
struct TYPE_2__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  happy_meal_begin_auto_negotiation (struct happy_meal*,int /*<<< orphan*/ ,struct ethtool_link_ksettings const*) ; 
 struct happy_meal* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hme_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct happy_meal *hp = netdev_priv(dev);

	/* Verify the settings we care about. */
	if (cmd->base.autoneg != AUTONEG_ENABLE &&
	    cmd->base.autoneg != AUTONEG_DISABLE)
		return -EINVAL;
	if (cmd->base.autoneg == AUTONEG_DISABLE &&
	    ((cmd->base.speed != SPEED_100 &&
	      cmd->base.speed != SPEED_10) ||
	     (cmd->base.duplex != DUPLEX_HALF &&
	      cmd->base.duplex != DUPLEX_FULL)))
		return -EINVAL;

	/* Ok, do it to it. */
	spin_lock_irq(&hp->happy_lock);
	del_timer(&hp->happy_timer);
	happy_meal_begin_auto_negotiation(hp, hp->tcvregs, cmd);
	spin_unlock_irq(&hp->happy_lock);

	return 0;
}