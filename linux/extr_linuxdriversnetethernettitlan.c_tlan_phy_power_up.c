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
typedef  int /*<<< orphan*/  u16 ;
struct tlan_priv {size_t phy_num; int /*<<< orphan*/ * phy; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_GC_LOOPBK ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_RESET ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_mii_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_set_timer (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlan_phy_power_up(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u16		value;

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Powering up PHY.\n", dev->name);
	tlan_mii_sync(dev->base_addr);
	value = MII_GC_LOOPBK;
	tlan_mii_write_reg(dev, priv->phy[priv->phy_num], MII_GEN_CTL, value);
	tlan_mii_sync(dev->base_addr);
	/* Wait for 500 ms and reset the
	 * transceiver.  The TLAN docs say both 50 ms and
	 * 500 ms, so do the longer, just in case.
	 */
	tlan_set_timer(dev, msecs_to_jiffies(500), TLAN_TIMER_PHY_RESET);

}