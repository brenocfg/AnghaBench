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
struct stmmac_priv {TYPE_1__* plat; struct net_device* dev; } ;
struct phy_device {int /*<<< orphan*/  speed; } ;
struct net_device {struct phy_device* phydev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bsp_priv; int /*<<< orphan*/  (* fix_mac_speed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void stmmac_hw_fix_mac_speed(struct stmmac_priv *priv)
{
	struct net_device *ndev = priv->dev;
	struct phy_device *phydev = ndev->phydev;

	if (likely(priv->plat->fix_mac_speed))
		priv->plat->fix_mac_speed(priv->plat->bsp_priv, phydev->speed);
}