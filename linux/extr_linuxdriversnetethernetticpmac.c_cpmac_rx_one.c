#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; } ;
struct cpmac_priv {TYPE_2__* dev; int /*<<< orphan*/  regs; } ;
struct cpmac_desc {int /*<<< orphan*/  dataflags; int /*<<< orphan*/  buflen; scalar_t__ data_mapping; scalar_t__ hw_data; struct sk_buff* skb; scalar_t__ datalen; scalar_t__ mapping; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_9__ {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_OWN ; 
 int /*<<< orphan*/  CPMAC_RX_ACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPMAC_SKB_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  cpmac_dump_desc (TYPE_2__*,struct cpmac_desc*) ; 
 int /*<<< orphan*/  cpmac_dump_skb (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*) ; 
 int netif_msg_hw (struct cpmac_priv*) ; 
 int netif_msg_pktdata (struct cpmac_priv*) ; 
 scalar_t__ netif_msg_rx_err (struct cpmac_priv*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *cpmac_rx_one(struct cpmac_priv *priv,
				    struct cpmac_desc *desc)
{
	struct sk_buff *skb, *result = NULL;

	if (unlikely(netif_msg_hw(priv)))
		cpmac_dump_desc(priv->dev, desc);
	cpmac_write(priv->regs, CPMAC_RX_ACK(0), (u32)desc->mapping);
	if (unlikely(!desc->datalen)) {
		if (netif_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev, "rx: spurious interrupt\n");

		return NULL;
	}

	skb = netdev_alloc_skb_ip_align(priv->dev, CPMAC_SKB_SIZE);
	if (likely(skb)) {
		skb_put(desc->skb, desc->datalen);
		desc->skb->protocol = eth_type_trans(desc->skb, priv->dev);
		skb_checksum_none_assert(desc->skb);
		priv->dev->stats.rx_packets++;
		priv->dev->stats.rx_bytes += desc->datalen;
		result = desc->skb;
		dma_unmap_single(&priv->dev->dev, desc->data_mapping,
				 CPMAC_SKB_SIZE, DMA_FROM_DEVICE);
		desc->skb = skb;
		desc->data_mapping = dma_map_single(&priv->dev->dev, skb->data,
						    CPMAC_SKB_SIZE,
						    DMA_FROM_DEVICE);
		desc->hw_data = (u32)desc->data_mapping;
		if (unlikely(netif_msg_pktdata(priv))) {
			netdev_dbg(priv->dev, "received packet:\n");
			cpmac_dump_skb(priv->dev, result);
		}
	} else {
		if (netif_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev,
				    "low on skbs, dropping packet\n");

		priv->dev->stats.rx_dropped++;
	}

	desc->buflen = CPMAC_SKB_SIZE;
	desc->dataflags = CPMAC_OWN;

	return result;
}