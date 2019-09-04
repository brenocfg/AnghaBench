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
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ len; } ;
struct efx_tx_queue {int /*<<< orphan*/  read_count; int /*<<< orphan*/  queue; TYPE_2__* efx; scalar_t__ completed_timestamp_minor; scalar_t__ completed_timestamp_major; scalar_t__ timestamping; } ;
struct efx_tx_buffer {int flags; scalar_t__ len; scalar_t__ skb; scalar_t__ unmap_len; scalar_t__ dma_offset; scalar_t__ dma_addr; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFX_TX_BUF_MAP_SINGLE ; 
 int EFX_TX_BUF_SKB ; 
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ptp_nic_to_kernel_time (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  netif_vdbg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  tx_done ; 

__attribute__((used)) static void efx_dequeue_buffer(struct efx_tx_queue *tx_queue,
			       struct efx_tx_buffer *buffer,
			       unsigned int *pkts_compl,
			       unsigned int *bytes_compl)
{
	if (buffer->unmap_len) {
		struct device *dma_dev = &tx_queue->efx->pci_dev->dev;
		dma_addr_t unmap_addr = buffer->dma_addr - buffer->dma_offset;
		if (buffer->flags & EFX_TX_BUF_MAP_SINGLE)
			dma_unmap_single(dma_dev, unmap_addr, buffer->unmap_len,
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dma_dev, unmap_addr, buffer->unmap_len,
				       DMA_TO_DEVICE);
		buffer->unmap_len = 0;
	}

	if (buffer->flags & EFX_TX_BUF_SKB) {
		struct sk_buff *skb = (struct sk_buff *)buffer->skb;

		EFX_WARN_ON_PARANOID(!pkts_compl || !bytes_compl);
		(*pkts_compl)++;
		(*bytes_compl) += skb->len;
		if (tx_queue->timestamping &&
		    (tx_queue->completed_timestamp_major ||
		     tx_queue->completed_timestamp_minor)) {
			struct skb_shared_hwtstamps hwtstamp;

			hwtstamp.hwtstamp =
				efx_ptp_nic_to_kernel_time(tx_queue);
			skb_tstamp_tx(skb, &hwtstamp);

			tx_queue->completed_timestamp_major = 0;
			tx_queue->completed_timestamp_minor = 0;
		}
		dev_consume_skb_any((struct sk_buff *)buffer->skb);
		netif_vdbg(tx_queue->efx, tx_done, tx_queue->efx->net_dev,
			   "TX queue %d transmission id %x complete\n",
			   tx_queue->queue, tx_queue->read_count);
	}

	buffer->len = 0;
	buffer->flags = 0;
}