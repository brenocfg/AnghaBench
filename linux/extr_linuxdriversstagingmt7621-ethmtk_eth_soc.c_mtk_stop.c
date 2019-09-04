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
struct mtk_eth {TYPE_2__* soc; int /*<<< orphan*/  rx_napi; int /*<<< orphan*/  dma_refcnt; TYPE_1__* phy; } ;
struct TYPE_4__ {int tx_int; int rx_int; int dma_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stop ) (struct mtk_mac*) ;} ;

/* Variables and functions */
 int MTK_PDMA ; 
 int MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QDMA_GLO_CFG ; 
 size_t MTK_REG_PDMA_GLO_CFG ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_dma_free (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_irq_disable (struct mtk_eth*,int) ; 
 int /*<<< orphan*/ * mtk_reg_table ; 
 int /*<<< orphan*/  mtk_stop_dma (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mtk_mac*) ; 

__attribute__((used)) static int mtk_stop(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;

	netif_tx_disable(dev);
	if (eth->phy)
		eth->phy->stop(mac);

	if (!atomic_dec_and_test(&eth->dma_refcnt))
		return 0;

	mtk_irq_disable(eth, eth->soc->tx_int | eth->soc->rx_int);
	napi_disable(&eth->rx_napi);

	if (eth->soc->dma_type & MTK_PDMA)
		mtk_stop_dma(eth, mtk_reg_table[MTK_REG_PDMA_GLO_CFG]);

	if (eth->soc->dma_type & MTK_QDMA)
		mtk_stop_dma(eth, MTK_QDMA_GLO_CFG);

	mtk_dma_free(eth);

	return 0;
}