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
struct usbnet {int /*<<< orphan*/  net; struct ax88172a_private* driver_priv; } ;
struct ax88172a_private {scalar_t__ phydev; int /*<<< orphan*/  phy_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int ax88172a_stop(struct usbnet *dev)
{
	struct ax88172a_private *priv = dev->driver_priv;

	netdev_dbg(dev->net, "Stopping interface\n");

	if (priv->phydev) {
		netdev_info(dev->net, "Disconnecting from phy %s\n",
			    priv->phy_name);
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
	}

	return 0;
}