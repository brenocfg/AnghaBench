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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct hmeal_init_block {int /*<<< orphan*/ * happy_meal_txd; int /*<<< orphan*/ * happy_meal_rxd; } ;
struct happy_meal {int /*<<< orphan*/  dma_dev; struct sk_buff** rx_skbs; scalar_t__ tx_old; scalar_t__ tx_new; scalar_t__ rx_old; scalar_t__ rx_new; struct hmeal_init_block* happy_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETH_FRAME_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HMD (char*) ; 
 int RXFLAG_OWN ; 
 int RX_BUF_ALLOC_SIZE ; 
 int RX_OFFSET ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* happy_meal_alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  happy_meal_clean_rings (struct happy_meal*) ; 
 int /*<<< orphan*/  hme_write_rxd (struct happy_meal*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hme_write_txd (struct happy_meal*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void happy_meal_init_rings(struct happy_meal *hp)
{
	struct hmeal_init_block *hb = hp->happy_block;
	int i;

	HMD(("happy_meal_init_rings: counters to zero, "));
	hp->rx_new = hp->rx_old = hp->tx_new = hp->tx_old = 0;

	/* Free any skippy bufs left around in the rings. */
	HMD(("clean, "));
	happy_meal_clean_rings(hp);

	/* Now get new skippy bufs for the receive ring. */
	HMD(("init rxring, "));
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb;
		u32 mapping;

		skb = happy_meal_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
		if (!skb) {
			hme_write_rxd(hp, &hb->happy_meal_rxd[i], 0, 0);
			continue;
		}
		hp->rx_skbs[i] = skb;

		/* Because we reserve afterwards. */
		skb_put(skb, (ETH_FRAME_LEN + RX_OFFSET + 4));
		mapping = dma_map_single(hp->dma_dev, skb->data, RX_BUF_ALLOC_SIZE,
					 DMA_FROM_DEVICE);
		if (dma_mapping_error(hp->dma_dev, mapping)) {
			dev_kfree_skb_any(skb);
			hme_write_rxd(hp, &hb->happy_meal_rxd[i], 0, 0);
			continue;
		}
		hme_write_rxd(hp, &hb->happy_meal_rxd[i],
			      (RXFLAG_OWN | ((RX_BUF_ALLOC_SIZE - RX_OFFSET) << 16)),
			      mapping);
		skb_reserve(skb, RX_OFFSET);
	}

	HMD(("init txring, "));
	for (i = 0; i < TX_RING_SIZE; i++)
		hme_write_txd(hp, &hb->happy_meal_txd[i], 0, 0);

	HMD(("done\n"));
}