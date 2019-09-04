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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct b43_dmaring {int /*<<< orphan*/  rx_buffersize; TYPE_2__* ops; TYPE_1__* dev; int /*<<< orphan*/  tx; } ;
struct b43_dmadesc_meta {int /*<<< orphan*/  dmaaddr; struct sk_buff* skb; } ;
struct b43_dmadesc_generic {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* fill_descriptor ) (struct b43_dmaring*,struct b43_dmadesc_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_dma_mapping_error (struct b43_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_poison_rx_buffer (struct b43_dmaring*,struct sk_buff*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  map_descbuffer (struct b43_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct b43_dmaring*,struct b43_dmadesc_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int setup_rx_descbuffer(struct b43_dmaring *ring,
			       struct b43_dmadesc_generic *desc,
			       struct b43_dmadesc_meta *meta, gfp_t gfp_flags)
{
	dma_addr_t dmaaddr;
	struct sk_buff *skb;

	B43_WARN_ON(ring->tx);

	skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
	if (unlikely(!skb))
		return -ENOMEM;
	b43_poison_rx_buffer(ring, skb);
	dmaaddr = map_descbuffer(ring, skb->data, ring->rx_buffersize, 0);
	if (b43_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {
		/* ugh. try to realloc in zone_dma */
		gfp_flags |= GFP_DMA;

		dev_kfree_skb_any(skb);

		skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
		if (unlikely(!skb))
			return -ENOMEM;
		b43_poison_rx_buffer(ring, skb);
		dmaaddr = map_descbuffer(ring, skb->data,
					 ring->rx_buffersize, 0);
		if (b43_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {
			b43err(ring->dev->wl, "RX DMA buffer allocation failed\n");
			dev_kfree_skb_any(skb);
			return -EIO;
		}
	}

	meta->skb = skb;
	meta->dmaaddr = dmaaddr;
	ring->ops->fill_descriptor(ring, desc, dmaaddr,
				   ring->rx_buffersize, 0, 0, 0);

	return 0;
}