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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct fe_priv {TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mac ) (struct fe_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  fe_hw_set_macaddr (struct fe_priv*,void*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct fe_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fe_set_mac_address(struct net_device *dev, void *p)
{
	int ret = eth_mac_addr(dev, p);

	if (!ret) {
		struct fe_priv *priv = netdev_priv(dev);

		if (priv->soc->set_mac)
			priv->soc->set_mac(priv, dev->dev_addr);
		else
			fe_hw_set_macaddr(priv, p);
	}

	return ret;
}