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
struct sk_buff {int dummy; } ;
struct ef4_tx_queue {int /*<<< orphan*/  read_count; int /*<<< orphan*/  queue; TYPE_3__* efx; } ;
struct ef4_tx_buffer {int flags; scalar_t__ len; TYPE_2__* skb; scalar_t__ unmap_len; scalar_t__ dma_offset; scalar_t__ dma_addr; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EF4_TX_BUF_MAP_SINGLE ; 
 int EF4_TX_BUF_SKB ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_vdbg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_done ; 

__attribute__((used)) static void ef4_dequeue_buffer(struct ef4_tx_queue *tx_queue,
			       struct ef4_tx_buffer *buffer,
			       unsigned int *pkts_compl,
			       unsigned int *bytes_compl)
{
	if (buffer->unmap_len) {
		struct device *dma_dev = &tx_queue->efx->pci_dev->dev;
		dma_addr_t unmap_addr = buffer->dma_addr - buffer->dma_offset;
		if (buffer->flags & EF4_TX_BUF_MAP_SINGLE)
			dma_unmap_single(dma_dev, unmap_addr, buffer->unmap_len,
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dma_dev, unmap_addr, buffer->unmap_len,
				       DMA_TO_DEVICE);
		buffer->unmap_len = 0;
	}

	if (buffer->flags & EF4_TX_BUF_SKB) {
		(*pkts_compl)++;
		(*bytes_compl) += buffer->skb->len;
		dev_consume_skb_any((struct sk_buff *)buffer->skb);
		netif_vdbg(tx_queue->efx, tx_done, tx_queue->efx->net_dev,
			   "TX queue %d transmission id %x complete\n",
			   tx_queue->queue, tx_queue->read_count);
	}

	buffer->len = 0;
	buffer->flags = 0;
}