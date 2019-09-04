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
struct efx_tx_queue {scalar_t__ insert_count; scalar_t__ read_count; TYPE_2__* efx; } ;
struct efx_tx_buffer {unsigned int dma_addr; unsigned int len; int /*<<< orphan*/  flags; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_4__ {scalar_t__ txq_entries; TYPE_1__* type; } ;
struct TYPE_3__ {unsigned int (* tx_limit_len ) (struct efx_tx_queue*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_TX_BUF_CONT ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 struct efx_tx_buffer* efx_tx_queue_get_insert_buffer (struct efx_tx_queue*) ; 
 unsigned int stub1 (struct efx_tx_queue*,unsigned int,unsigned int) ; 

__attribute__((used)) static void efx_tx_queue_insert(struct efx_tx_queue *tx_queue,
				dma_addr_t dma_addr, unsigned int len,
				struct efx_tx_buffer **final_buffer)
{
	struct efx_tx_buffer *buffer;
	unsigned int dma_len;

	EFX_WARN_ON_ONCE_PARANOID(len <= 0);

	while (1) {
		buffer = efx_tx_queue_get_insert_buffer(tx_queue);
		++tx_queue->insert_count;

		EFX_WARN_ON_ONCE_PARANOID(tx_queue->insert_count -
					  tx_queue->read_count >=
					  tx_queue->efx->txq_entries);

		buffer->dma_addr = dma_addr;

		dma_len = tx_queue->efx->type->tx_limit_len(tx_queue,
				dma_addr, len);

		/* If there's space for everything this is our last buffer. */
		if (dma_len >= len)
			break;

		buffer->len = dma_len;
		buffer->flags = EFX_TX_BUF_CONT;
		dma_addr += dma_len;
		len -= dma_len;
	}

	EFX_WARN_ON_ONCE_PARANOID(!len);
	buffer->len = len;
	*final_buffer = buffer;
}