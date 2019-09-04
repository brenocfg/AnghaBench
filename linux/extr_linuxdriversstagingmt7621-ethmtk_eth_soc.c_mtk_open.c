#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_2__* soc; TYPE_1__* phy; int /*<<< orphan*/  dma_refcnt; int /*<<< orphan*/  rx_napi; } ;
struct TYPE_4__ {int tx_int; int rx_int; int /*<<< orphan*/  (* fwd_config ) (struct mtk_eth*) ;scalar_t__ (* has_carrier ) (struct mtk_eth*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* start ) (struct mtk_mac*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_irq_enable (struct mtk_eth*,int) ; 
 int mtk_start_dma (struct mtk_eth*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mtk_mac*) ; 
 scalar_t__ stub2 (struct mtk_eth*) ; 
 int /*<<< orphan*/  stub3 (struct mtk_eth*) ; 

__attribute__((used)) static int mtk_open(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	if (!atomic_read(&eth->dma_refcnt)) {
		int err = mtk_start_dma(eth);

		if (err)
			return err;

		napi_enable(&eth->rx_napi);
		mtk_irq_enable(eth, eth->soc->tx_int | eth->soc->rx_int);
	}
	atomic_inc(&eth->dma_refcnt);

	if (eth->phy)
		eth->phy->start(mac);

	if (eth->soc->has_carrier && eth->soc->has_carrier(eth))
		netif_carrier_on(dev);

	netif_start_queue(dev);
	eth->soc->fwd_config(eth);

	return 0;
}