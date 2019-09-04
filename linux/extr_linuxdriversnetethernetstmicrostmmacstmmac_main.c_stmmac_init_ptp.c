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
struct TYPE_4__ {scalar_t__ time_stamp; scalar_t__ atime_stamp; } ;
struct stmmac_priv {int adv_ts; scalar_t__ hwts_rx_en; scalar_t__ hwts_tx_en; int /*<<< orphan*/  dev; TYPE_2__ dma_cap; scalar_t__ extend_desc; TYPE_1__* plat; } ;
struct TYPE_3__ {scalar_t__ has_xgmac; scalar_t__ has_gmac4; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stmmac_ptp_register (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_init_ptp(struct stmmac_priv *priv)
{
	bool xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

	if (!(priv->dma_cap.time_stamp || priv->dma_cap.atime_stamp))
		return -EOPNOTSUPP;

	priv->adv_ts = 0;
	/* Check if adv_ts can be enabled for dwmac 4.x / xgmac core */
	if (xmac && priv->dma_cap.atime_stamp)
		priv->adv_ts = 1;
	/* Dwmac 3.x core with extend_desc can support adv_ts */
	else if (priv->extend_desc && priv->dma_cap.atime_stamp)
		priv->adv_ts = 1;

	if (priv->dma_cap.time_stamp)
		netdev_info(priv->dev, "IEEE 1588-2002 Timestamp supported\n");

	if (priv->adv_ts)
		netdev_info(priv->dev,
			    "IEEE 1588-2008 Advanced Timestamp supported\n");

	priv->hwts_tx_en = 0;
	priv->hwts_rx_en = 0;

	stmmac_ptp_register(priv);

	return 0;
}