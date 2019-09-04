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
struct xlr_net_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  mii_bus; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct xlr_net_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlr_net_remove(struct platform_device *pdev)
{
	struct xlr_net_priv *priv = platform_get_drvdata(pdev);

	unregister_netdev(priv->ndev);
	mdiobus_unregister(priv->mii_bus);
	mdiobus_free(priv->mii_bus);
	free_netdev(priv->ndev);
	return 0;
}