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
struct rhine_private {int quirks; int /*<<< orphan*/  lock; int /*<<< orphan*/  wolopts; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int /*<<< orphan*/  wolopts; } ;

/* Variables and functions */
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int rqWOL ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rhine_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct rhine_private *rp = netdev_priv(dev);

	if (!(rp->quirks & rqWOL))
		return;

	spin_lock_irq(&rp->lock);
	wol->supported = WAKE_PHY | WAKE_MAGIC |
			 WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;	/* Untested */
	wol->wolopts = rp->wolopts;
	spin_unlock_irq(&rp->lock);
}