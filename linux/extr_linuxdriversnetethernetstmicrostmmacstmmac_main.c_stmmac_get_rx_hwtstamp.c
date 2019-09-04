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
typedef  int /*<<< orphan*/  u64 ;
struct stmmac_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  adv_ts; TYPE_1__* plat; int /*<<< orphan*/  hwts_rx_en; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct dma_desc {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_xgmac; scalar_t__ has_gmac4; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 scalar_t__ stmmac_get_rx_timestamp_status (struct stmmac_priv*,struct dma_desc*,struct dma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_get_timestamp (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stmmac_get_rx_hwtstamp(struct stmmac_priv *priv, struct dma_desc *p,
				   struct dma_desc *np, struct sk_buff *skb)
{
	struct skb_shared_hwtstamps *shhwtstamp = NULL;
	struct dma_desc *desc = p;
	u64 ns = 0;

	if (!priv->hwts_rx_en)
		return;
	/* For GMAC4, the valid timestamp is from CTX next desc. */
	if (priv->plat->has_gmac4 || priv->plat->has_xgmac)
		desc = np;

	/* Check if timestamp is available */
	if (stmmac_get_rx_timestamp_status(priv, p, np, priv->adv_ts)) {
		stmmac_get_timestamp(priv, desc, priv->adv_ts, &ns);
		netdev_dbg(priv->dev, "get valid RX hw timestamp %llu\n", ns);
		shhwtstamp = skb_hwtstamps(skb);
		memset(shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));
		shhwtstamp->hwtstamp = ns_to_ktime(ns);
	} else  {
		netdev_dbg(priv->dev, "cannot get RX hw timestamp\n");
	}
}