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
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct fe_tx_ring {struct fe_tx_buf* tx_buf; } ;
struct fe_tx_buf {struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  txd2; void* txd1; void* txd3; } ;
struct fe_map_state {int i; size_t ring_idx; TYPE_1__ txd; struct device* dev; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  TX_DMA_PLEN0 (size_t) ; 
 int /*<<< orphan*/  TX_DMA_PLEN1 (size_t) ; 
 int /*<<< orphan*/  dma_addr0 ; 
 int /*<<< orphan*/  dma_addr1 ; 
 int /*<<< orphan*/  dma_len0 ; 
 int /*<<< orphan*/  dma_len1 ; 
 void* dma_map_page (struct device*,struct page*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct fe_tx_buf*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct fe_tx_buf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fe_tx_dma_write_desc (struct fe_tx_ring*,struct fe_map_state*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __fe_tx_dma_map_page(struct fe_tx_ring *ring, struct fe_map_state *st,
				struct page *page, size_t offset, size_t size)
{
	struct device *dev = st->dev;
	struct fe_tx_buf *tx_buf;
	dma_addr_t mapped_addr;

	mapped_addr = dma_map_page(dev, page, offset, size, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(dev, mapped_addr)))
		return -EIO;

	if (st->i && !(st->i & 1))
	    fe_tx_dma_write_desc(ring, st);

	tx_buf = &ring->tx_buf[st->ring_idx];
	if (st->i & 1) {
		st->txd.txd3 = mapped_addr;
		st->txd.txd2 |= TX_DMA_PLEN1(size);
		dma_unmap_addr_set(tx_buf, dma_addr1, mapped_addr);
		dma_unmap_len_set(tx_buf, dma_len1, size);
	} else {
		tx_buf->skb = (struct sk_buff *)DMA_DUMMY_DESC;
		st->txd.txd1 = mapped_addr;
		st->txd.txd2 = TX_DMA_PLEN0(size);
		dma_unmap_addr_set(tx_buf, dma_addr0, mapped_addr);
		dma_unmap_len_set(tx_buf, dma_len0, size);
	}
	st->i++;

	return 0;
}