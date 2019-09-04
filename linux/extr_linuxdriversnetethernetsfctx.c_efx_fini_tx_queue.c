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
struct efx_tx_queue {size_t read_count; size_t write_count; size_t ptr_mask; int xmit_more_available; int /*<<< orphan*/  core_txq; struct efx_tx_buffer* buffer; int /*<<< orphan*/  queue; TYPE_1__* efx; } ;
struct efx_tx_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_dequeue_buffer (struct efx_tx_queue*,struct efx_tx_buffer*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void efx_fini_tx_queue(struct efx_tx_queue *tx_queue)
{
	struct efx_tx_buffer *buffer;

	netif_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "shutting down TX queue %d\n", tx_queue->queue);

	if (!tx_queue->buffer)
		return;

	/* Free any buffers left in the ring */
	while (tx_queue->read_count != tx_queue->write_count) {
		unsigned int pkts_compl = 0, bytes_compl = 0;
		buffer = &tx_queue->buffer[tx_queue->read_count & tx_queue->ptr_mask];
		efx_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);

		++tx_queue->read_count;
	}
	tx_queue->xmit_more_available = false;
	netdev_tx_reset_queue(tx_queue->core_txq);
}