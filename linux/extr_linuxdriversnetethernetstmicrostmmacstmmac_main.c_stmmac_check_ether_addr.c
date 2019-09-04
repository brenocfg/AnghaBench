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
struct stmmac_priv {TYPE_1__* dev; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_1__*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_get_umac_addr (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_check_ether_addr(struct stmmac_priv *priv)
{
	if (!is_valid_ether_addr(priv->dev->dev_addr)) {
		stmmac_get_umac_addr(priv, priv->hw, priv->dev->dev_addr, 0);
		if (!is_valid_ether_addr(priv->dev->dev_addr))
			eth_hw_addr_random(priv->dev);
		netdev_info(priv->dev, "device MAC address %pM\n",
			    priv->dev->dev_addr);
	}
}