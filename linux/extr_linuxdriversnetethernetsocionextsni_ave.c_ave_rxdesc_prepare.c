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
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  tail; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {TYPE_2__* desc; } ;
struct ave_private {TYPE_1__ rx; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {struct sk_buff* skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESCID_RX ; 
 scalar_t__ AVE_FRAME_HEADROOM ; 
 int AVE_MAX_ETHFRAME ; 
 int AVE_STS_INTR ; 
 int AVE_STS_OWN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ave_desc_write_addr (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_desc_write_cmdsts (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int ave_dma_map (struct net_device*,TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ave_rxdesc_prepare(struct net_device *ndev, int entry)
{
	struct ave_private *priv = netdev_priv(ndev);
	struct sk_buff *skb;
	dma_addr_t paddr;
	int ret;

	skb = priv->rx.desc[entry].skbs;
	if (!skb) {
		skb = netdev_alloc_skb(ndev, AVE_MAX_ETHFRAME);
		if (!skb) {
			netdev_err(ndev, "can't allocate skb for Rx\n");
			return -ENOMEM;
		}
		skb->data += AVE_FRAME_HEADROOM;
		skb->tail += AVE_FRAME_HEADROOM;
	}

	/* set disable to cmdsts */
	ave_desc_write_cmdsts(ndev, AVE_DESCID_RX, entry,
			      AVE_STS_INTR | AVE_STS_OWN);

	/* map Rx buffer
	 * Rx buffer set to the Rx descriptor has two restrictions:
	 * - Rx buffer address is 4 byte aligned.
	 * - Rx buffer begins with 2 byte headroom, and data will be put from
	 *   (buffer + 2).
	 * To satisfy this, specify the address to put back the buffer
	 * pointer advanced by AVE_FRAME_HEADROOM, and expand the map size
	 * by AVE_FRAME_HEADROOM.
	 */
	ret = ave_dma_map(ndev, &priv->rx.desc[entry],
			  skb->data - AVE_FRAME_HEADROOM,
			  AVE_MAX_ETHFRAME + AVE_FRAME_HEADROOM,
			  DMA_FROM_DEVICE, &paddr);
	if (ret) {
		netdev_err(ndev, "can't map skb for Rx\n");
		dev_kfree_skb_any(skb);
		return ret;
	}
	priv->rx.desc[entry].skbs = skb;

	/* set buffer pointer */
	ave_desc_write_addr(ndev, AVE_DESCID_RX, entry, paddr);

	/* set enable to cmdsts */
	ave_desc_write_cmdsts(ndev, AVE_DESCID_RX, entry,
			      AVE_STS_INTR | AVE_MAX_ETHFRAME);

	return ret;
}