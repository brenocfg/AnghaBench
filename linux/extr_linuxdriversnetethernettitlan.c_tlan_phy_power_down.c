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
typedef  int u16 ;
struct tlan_priv {scalar_t__* phy; size_t phy_num; TYPE_1__* adapter; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MII_GC_ISOLATE ; 
 int MII_GC_LOOPBK ; 
 int MII_GC_PDOWN ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int TLAN_ADAPTER_USE_INTERN_10 ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 scalar_t__ TLAN_PHY_NONE ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_PUP ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_mii_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_set_timer (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlan_phy_power_down(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u16		value;

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Powering down PHY(s).\n", dev->name);
	value = MII_GC_PDOWN | MII_GC_LOOPBK | MII_GC_ISOLATE;
	tlan_mii_sync(dev->base_addr);
	tlan_mii_write_reg(dev, priv->phy[priv->phy_num], MII_GEN_CTL, value);
	if ((priv->phy_num == 0) && (priv->phy[1] != TLAN_PHY_NONE)) {
		/* if using internal PHY, the external PHY must be powered on */
		if (priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10)
			value = MII_GC_ISOLATE; /* just isolate it from MII */
		tlan_mii_sync(dev->base_addr);
		tlan_mii_write_reg(dev, priv->phy[1], MII_GEN_CTL, value);
	}

	/* Wait for 50 ms and powerup
	 * This is abitrary.  It is intended to make sure the
	 * transceiver settles.
	 */
	tlan_set_timer(dev, msecs_to_jiffies(50), TLAN_TIMER_PHY_PUP);

}