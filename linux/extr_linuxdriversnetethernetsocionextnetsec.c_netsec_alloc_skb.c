#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct netsec_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev; } ;
struct netsec_desc {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ DEV_DMA_COHERENT ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  L1_CACHE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ device_get_dma_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *netsec_alloc_skb(struct netsec_priv *priv,
					struct netsec_desc *desc)
{
	struct sk_buff *skb;

	if (device_get_dma_attr(priv->dev) == DEV_DMA_COHERENT) {
		skb = netdev_alloc_skb_ip_align(priv->ndev, desc->len);
	} else {
		desc->len = L1_CACHE_ALIGN(desc->len);
		skb = netdev_alloc_skb(priv->ndev, desc->len);
	}
	if (!skb)
		return NULL;

	desc->addr = skb->data;
	desc->dma_addr = dma_map_single(priv->dev, desc->addr, desc->len,
					DMA_FROM_DEVICE);
	if (dma_mapping_error(priv->dev, desc->dma_addr)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}
	return skb;
}