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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct device {int dummy; } ;
struct net_device {TYPE_1__ stats; struct device dev; } ;
struct emac_priv {int /*<<< orphan*/  txchan; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_DEF_MIN_ETHPKTSIZE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int cpdma_chan_submit (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_check_free_tx_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ net_ratelimit () ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct emac_priv*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int skb_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int emac_dev_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct device *emac_dev = &ndev->dev;
	int ret_code;
	struct emac_priv *priv = netdev_priv(ndev);

	/* If no link, return */
	if (unlikely(!priv->link)) {
		if (netif_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: No link to transmit");
		goto fail_tx;
	}

	ret_code = skb_padto(skb, EMAC_DEF_MIN_ETHPKTSIZE);
	if (unlikely(ret_code < 0)) {
		if (netif_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: packet pad failed");
		goto fail_tx;
	}

	skb_tx_timestamp(skb);

	ret_code = cpdma_chan_submit(priv->txchan, skb, skb->data, skb->len,
				     0);
	if (unlikely(ret_code != 0)) {
		if (netif_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: desc submit failed");
		goto fail_tx;
	}

	/* If there is no more tx desc left free then we need to
	 * tell the kernel to stop sending us tx frames.
	 */
	if (unlikely(!cpdma_check_free_tx_desc(priv->txchan)))
		netif_stop_queue(ndev);

	return NETDEV_TX_OK;

fail_tx:
	ndev->stats.tx_dropped++;
	netif_stop_queue(ndev);
	return NETDEV_TX_BUSY;
}