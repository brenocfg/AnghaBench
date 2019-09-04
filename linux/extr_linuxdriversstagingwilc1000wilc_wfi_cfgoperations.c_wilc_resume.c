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
struct wiphy {int dummy; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int wilc_resume(struct wiphy *wiphy)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	netdev_info(vif->ndev, "cfg resume\n");
	return 0;
}