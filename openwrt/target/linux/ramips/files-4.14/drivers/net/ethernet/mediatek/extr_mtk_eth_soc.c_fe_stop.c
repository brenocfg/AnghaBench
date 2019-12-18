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
struct fe_priv {int /*<<< orphan*/  page_lock; TYPE_2__* phy; int /*<<< orphan*/  rx_napi; TYPE_1__* soc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct fe_priv*) ;} ;
struct TYPE_3__ {int tx_int; int rx_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_REG_PDMA_GLO_CFG ; 
 int FE_RX_DMA_BUSY ; 
 int FE_RX_DMA_EN ; 
 int FE_TX_DMA_BUSY ; 
 int FE_TX_DMA_EN ; 
 int FE_TX_WB_DDONE ; 
 int /*<<< orphan*/  fe_free_dma (struct fe_priv*) ; 
 int /*<<< orphan*/  fe_int_disable (int) ; 
 int fe_reg_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_reg_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtk_ppe_remove (struct fe_priv*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct fe_priv*) ; 

__attribute__((used)) static int fe_stop(struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	unsigned long flags;
	int i;

	netif_tx_disable(dev);
	fe_int_disable(priv->soc->tx_int | priv->soc->rx_int);
	napi_disable(&priv->rx_napi);

	if (priv->phy)
		priv->phy->stop(priv);

	spin_lock_irqsave(&priv->page_lock, flags);

	fe_reg_w32(fe_reg_r32(FE_REG_PDMA_GLO_CFG) &
		     ~(FE_TX_WB_DDONE | FE_RX_DMA_EN | FE_TX_DMA_EN),
		     FE_REG_PDMA_GLO_CFG);
	spin_unlock_irqrestore(&priv->page_lock, flags);

	/* wait dma stop */
	for (i = 0; i < 10; i++) {
		if (fe_reg_r32(FE_REG_PDMA_GLO_CFG) &
				(FE_TX_DMA_BUSY | FE_RX_DMA_BUSY)) {
			msleep(20);
			continue;
		}
		break;
	}

	fe_free_dma(priv);

#ifdef CONFIG_NET_MEDIATEK_OFFLOAD
	mtk_ppe_remove(priv);
#endif

	return 0;
}