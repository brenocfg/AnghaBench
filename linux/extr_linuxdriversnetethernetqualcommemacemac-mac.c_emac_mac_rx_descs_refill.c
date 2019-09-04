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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int produce_idx; scalar_t__ count; } ;
struct emac_rx_queue {scalar_t__ produce_shift; scalar_t__ produce_mask; scalar_t__ produce_reg; TYPE_2__ rfd; } ;
struct emac_buffer {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  length; struct sk_buff* skb; } ;
struct emac_adapter {scalar_t__ base; int /*<<< orphan*/  rxbuf_size; TYPE_3__* netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct emac_buffer* GET_RFD_BUFFER (struct emac_rx_queue*,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_mac_rx_rfd_create (struct emac_adapter*,struct emac_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_reg_update32 (scalar_t__,scalar_t__,scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emac_mac_rx_descs_refill(struct emac_adapter *adpt,
				    struct emac_rx_queue *rx_q)
{
	struct emac_buffer *curr_rxbuf;
	struct emac_buffer *next_rxbuf;
	unsigned int count = 0;
	u32 next_produce_idx;

	next_produce_idx = rx_q->rfd.produce_idx + 1;
	if (next_produce_idx == rx_q->rfd.count)
		next_produce_idx = 0;

	curr_rxbuf = GET_RFD_BUFFER(rx_q, rx_q->rfd.produce_idx);
	next_rxbuf = GET_RFD_BUFFER(rx_q, next_produce_idx);

	/* this always has a blank rx_buffer*/
	while (!next_rxbuf->dma_addr) {
		struct sk_buff *skb;
		int ret;

		skb = netdev_alloc_skb_ip_align(adpt->netdev, adpt->rxbuf_size);
		if (!skb)
			break;

		curr_rxbuf->dma_addr =
			dma_map_single(adpt->netdev->dev.parent, skb->data,
				       adpt->rxbuf_size, DMA_FROM_DEVICE);

		ret = dma_mapping_error(adpt->netdev->dev.parent,
					curr_rxbuf->dma_addr);
		if (ret) {
			dev_kfree_skb(skb);
			break;
		}
		curr_rxbuf->skb = skb;
		curr_rxbuf->length = adpt->rxbuf_size;

		emac_mac_rx_rfd_create(adpt, rx_q, curr_rxbuf->dma_addr);
		next_produce_idx = rx_q->rfd.produce_idx + 1;
		if (next_produce_idx == rx_q->rfd.count)
			next_produce_idx = 0;

		curr_rxbuf = GET_RFD_BUFFER(rx_q, rx_q->rfd.produce_idx);
		next_rxbuf = GET_RFD_BUFFER(rx_q, next_produce_idx);
		count++;
	}

	if (count) {
		u32 prod_idx = (rx_q->rfd.produce_idx << rx_q->produce_shift) &
				rx_q->produce_mask;
		emac_reg_update32(adpt->base + rx_q->produce_reg,
				  rx_q->produce_mask, prod_idx);
	}
}