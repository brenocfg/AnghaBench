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
struct net_device {int dummy; } ;
struct ave_private {int nrsts; int nclks; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * rst; int /*<<< orphan*/  mdio; int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ave_uninit(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	int i;

	phy_disconnect(priv->phydev);
	mdiobus_unregister(priv->mdio);

	/* disable clk because of hw access after ndo_stop */
	for (i = 0; i < priv->nrsts; i++)
		reset_control_assert(priv->rst[i]);
	for (i = 0; i < priv->nclks; i++)
		clk_disable_unprepare(priv->clk[i]);
}