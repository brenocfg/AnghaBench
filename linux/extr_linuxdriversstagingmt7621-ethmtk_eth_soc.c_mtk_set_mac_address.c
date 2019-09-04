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
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mac ) (struct mtk_mac*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  mtk_hw_set_macaddr (struct mtk_mac*,void*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mtk_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_set_mac_address(struct net_device *dev, void *p)
{
	int ret = eth_mac_addr(dev, p);
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	if (ret)
		return ret;

	if (eth->soc->set_mac)
		eth->soc->set_mac(mac, dev->dev_addr);
	else
		mtk_hw_set_macaddr(mac, p);

	return 0;
}