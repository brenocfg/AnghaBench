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
struct efx_tx_queue {unsigned int ptr_mask; unsigned int read_count; int /*<<< orphan*/  queue; struct efx_tx_buffer* buffer; struct efx_nic* efx; } ;
struct efx_tx_buffer {int flags; scalar_t__ len; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EFX_TX_BUF_OPTION ; 
 int /*<<< orphan*/  RESET_TYPE_TX_SKIP ; 
 int /*<<< orphan*/  efx_dequeue_buffer (struct efx_tx_queue*,struct efx_tx_buffer*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void efx_dequeue_buffers(struct efx_tx_queue *tx_queue,
				unsigned int index,
				unsigned int *pkts_compl,
				unsigned int *bytes_compl)
{
	struct efx_nic *efx = tx_queue->efx;
	unsigned int stop_index, read_ptr;

	stop_index = (index + 1) & tx_queue->ptr_mask;
	read_ptr = tx_queue->read_count & tx_queue->ptr_mask;

	while (read_ptr != stop_index) {
		struct efx_tx_buffer *buffer = &tx_queue->buffer[read_ptr];

		if (!(buffer->flags & EFX_TX_BUF_OPTION) &&
		    unlikely(buffer->len == 0)) {
			netif_err(efx, tx_err, efx->net_dev,
				  "TX queue %d spurious TX completion id %x\n",
				  tx_queue->queue, read_ptr);
			efx_schedule_reset(efx, RESET_TYPE_TX_SKIP);
			return;
		}

		efx_dequeue_buffer(tx_queue, buffer, pkts_compl, bytes_compl);

		++tx_queue->read_count;
		read_ptr = tx_queue->read_count & tx_queue->ptr_mask;
	}
}