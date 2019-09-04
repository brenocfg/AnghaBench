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
struct rhine_private {int dummy; } ;
struct net_device {int dummy; } ;
struct mii_if_info {int /*<<< orphan*/  force_media; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct rhine_private*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhine_check_media (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rhine_set_carrier(struct mii_if_info *mii)
{
	struct net_device *dev = mii->dev;
	struct rhine_private *rp = netdev_priv(dev);

	if (mii->force_media) {
		/* autoneg is off: Link is always assumed to be up */
		if (!netif_carrier_ok(dev))
			netif_carrier_on(dev);
	}

	rhine_check_media(dev, 0);

	netif_info(rp, link, dev, "force_media %d, carrier %d\n",
		   mii->force_media, netif_carrier_ok(dev));
}