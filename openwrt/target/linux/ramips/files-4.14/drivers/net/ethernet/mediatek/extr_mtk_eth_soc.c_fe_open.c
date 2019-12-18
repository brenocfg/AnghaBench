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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct fe_priv {int flags; TYPE_2__* soc; int /*<<< orphan*/  rx_napi; TYPE_1__* phy; int /*<<< orphan*/  page_lock; } ;
struct TYPE_4__ {int pdma_glo_cfg; int tx_int; int rx_int; scalar_t__ (* has_carrier ) (struct fe_priv*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* start ) (struct fe_priv*) ;} ;

/* Variables and functions */
 int FE_FLAG_RX_2B_OFFSET ; 
 int /*<<< orphan*/  FE_REG_PDMA_GLO_CFG ; 
 int FE_RX_2B_OFFSET ; 
 int FE_RX_DMA_EN ; 
 int FE_TX_DMA_EN ; 
 int FE_TX_WB_DDONE ; 
 int /*<<< orphan*/  fe_free_dma (struct fe_priv*) ; 
 int fe_init_dma (struct fe_priv*) ; 
 int /*<<< orphan*/  fe_int_enable (int) ; 
 int /*<<< orphan*/  fe_reg_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_ppe_probe (struct fe_priv*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct fe_priv*) ; 
 scalar_t__ stub2 (struct fe_priv*) ; 

__attribute__((used)) static int fe_open(struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	unsigned long flags;
	u32 val;
	int err;

	err = fe_init_dma(priv);
	if (err) {
		fe_free_dma(priv);
		return err;
	}

	spin_lock_irqsave(&priv->page_lock, flags);

	val = FE_TX_WB_DDONE | FE_RX_DMA_EN | FE_TX_DMA_EN;
	if (priv->flags & FE_FLAG_RX_2B_OFFSET)
		val |= FE_RX_2B_OFFSET;
	val |= priv->soc->pdma_glo_cfg;
	fe_reg_w32(val, FE_REG_PDMA_GLO_CFG);

	spin_unlock_irqrestore(&priv->page_lock, flags);

	if (priv->phy)
		priv->phy->start(priv);

	if (priv->soc->has_carrier && priv->soc->has_carrier(priv))
		netif_carrier_on(dev);

	napi_enable(&priv->rx_napi);
	fe_int_enable(priv->soc->tx_int | priv->soc->rx_int);
	netif_start_queue(dev);
#ifdef CONFIG_NET_MEDIATEK_OFFLOAD
	mtk_ppe_probe(priv);
#endif

	return 0;
}