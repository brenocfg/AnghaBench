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
struct efx_tx_queue {int /*<<< orphan*/  insert_count; TYPE_1__* efx; } ;
struct efx_tx_buffer {unsigned int len; unsigned int dma_addr; int /*<<< orphan*/  flags; } ;
struct efx_nic_type {unsigned int (* tx_limit_len ) (struct efx_tx_queue*,unsigned int,size_t) ;} ;
typedef  unsigned int dma_addr_t ;
struct TYPE_2__ {struct efx_nic_type* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_TX_BUF_CONT ; 
 struct efx_tx_buffer* efx_tx_queue_get_insert_buffer (struct efx_tx_queue*) ; 
 unsigned int stub1 (struct efx_tx_queue*,unsigned int,size_t) ; 

__attribute__((used)) static struct efx_tx_buffer *efx_tx_map_chunk(struct efx_tx_queue *tx_queue,
					      dma_addr_t dma_addr,
					      size_t len)
{
	const struct efx_nic_type *nic_type = tx_queue->efx->type;
	struct efx_tx_buffer *buffer;
	unsigned int dma_len;

	/* Map the fragment taking account of NIC-dependent DMA limits. */
	do {
		buffer = efx_tx_queue_get_insert_buffer(tx_queue);
		dma_len = nic_type->tx_limit_len(tx_queue, dma_addr, len);

		buffer->len = dma_len;
		buffer->dma_addr = dma_addr;
		buffer->flags = EFX_TX_BUF_CONT;
		len -= dma_len;
		dma_addr += dma_len;
		++tx_queue->insert_count;
	} while (len);

	return buffer;
}