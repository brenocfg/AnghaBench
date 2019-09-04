#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbnet {int /*<<< orphan*/  net; struct ax88172a_private* driver_priv; } ;
struct ax88172a_private {TYPE_1__* mdio; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ax88172a_remove_mdio(struct usbnet *dev)
{
	struct ax88172a_private *priv = dev->driver_priv;

	netdev_info(dev->net, "deregistering mdio bus %s\n", priv->mdio->id);
	mdiobus_unregister(priv->mdio);
	mdiobus_free(priv->mdio);
}