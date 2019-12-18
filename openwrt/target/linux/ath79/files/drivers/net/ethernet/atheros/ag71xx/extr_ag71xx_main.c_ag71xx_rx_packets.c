#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int /*<<< orphan*/  name; TYPE_2__ stats; } ;
struct ag71xx_ring {int curr; int dirty; TYPE_3__* buf; int /*<<< orphan*/  order; } ;
struct ag71xx_desc {unsigned int ctrl; } ;
struct ag71xx {unsigned int desc_pktlen_mask; unsigned int rx_buf_offset; int /*<<< orphan*/  rx_buf_size; TYPE_1__* pdev; struct ag71xx_ring rx_ring; struct net_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_RX_STATUS ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  RX_STATUS_PR ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  ag71xx_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_buffer_size (struct ag71xx*) ; 
 scalar_t__ ag71xx_desc_empty (struct ag71xx_desc*) ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,unsigned int) ; 
 int /*<<< orphan*/  ag71xx_ring_rx_refill (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int ag71xx_rx_packets(struct ag71xx *ag, int limit)
{
	struct net_device *dev = ag->dev;
	struct ag71xx_ring *ring = &ag->rx_ring;
	unsigned int pktlen_mask = ag->desc_pktlen_mask;
	unsigned int offset = ag->rx_buf_offset;
	int ring_mask = BIT(ring->order) - 1;
	int ring_size = BIT(ring->order);
	struct sk_buff_head queue;
	struct sk_buff *skb;
	int done = 0;

	DBG("%s: rx packets, limit=%d, curr=%u, dirty=%u\n",
			dev->name, limit, ring->curr, ring->dirty);

	skb_queue_head_init(&queue);

	while (done < limit) {
		unsigned int i = ring->curr & ring_mask;
		struct ag71xx_desc *desc = ag71xx_ring_desc(ring, i);
		int pktlen;
		int err = 0;

		if (ag71xx_desc_empty(desc))
			break;

		if ((ring->dirty + ring_size) == ring->curr) {
			ag71xx_assert(0);
			break;
		}

		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);

		pktlen = desc->ctrl & pktlen_mask;
		pktlen -= ETH_FCS_LEN;

		dma_unmap_single(&ag->pdev->dev, ring->buf[i].dma_addr,
				 ag->rx_buf_size, DMA_FROM_DEVICE);

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pktlen;

		skb = build_skb(ring->buf[i].rx_buf, ag71xx_buffer_size(ag));
		if (!skb) {
			skb_free_frag(ring->buf[i].rx_buf);
			goto next;
		}

		skb_reserve(skb, offset);
		skb_put(skb, pktlen);

		if (err) {
			dev->stats.rx_dropped++;
			kfree_skb(skb);
		} else {
			skb->dev = dev;
			skb->ip_summed = CHECKSUM_NONE;
			__skb_queue_tail(&queue, skb);
		}

next:
		ring->buf[i].rx_buf = NULL;
		done++;

		ring->curr++;
	}

	ag71xx_ring_rx_refill(ag);

	while ((skb = __skb_dequeue(&queue)) != NULL) {
		skb->protocol = eth_type_trans(skb, dev);
		netif_receive_skb(skb);
	}

	DBG("%s: rx finish, curr=%u, dirty=%u, done=%d\n",
		dev->name, ring->curr, ring->dirty, done);

	return done;
}