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
struct tlan_priv {int* phy; size_t phy_num; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int MII_GC_LOOPBK ; 
 int MII_GC_RESET ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_START_LINK ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tlan_mii_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_set_timer (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlan_phy_reset(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u16		phy;
	u16		value;
	unsigned long timeout = jiffies + HZ;

	phy = priv->phy[priv->phy_num];

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Resetting PHY.\n", dev->name);
	tlan_mii_sync(dev->base_addr);
	value = MII_GC_LOOPBK | MII_GC_RESET;
	tlan_mii_write_reg(dev, phy, MII_GEN_CTL, value);
	do {
		tlan_mii_read_reg(dev, phy, MII_GEN_CTL, &value);
		if (time_after(jiffies, timeout)) {
			netdev_err(dev, "PHY reset timeout\n");
			return;
		}
	} while (value & MII_GC_RESET);

	/* Wait for 500 ms and initialize.
	 * I don't remember why I wait this long.
	 * I've changed this to 50ms, as it seems long enough.
	 */
	tlan_set_timer(dev, msecs_to_jiffies(50), TLAN_TIMER_PHY_START_LINK);

}