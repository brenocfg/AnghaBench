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
struct ef4_tx_queue {unsigned int write_count; int xmit_more_available; unsigned int insert_count; unsigned int ptr_mask; int /*<<< orphan*/  pushes; struct ef4_tx_buffer* buffer; } ;
struct ef4_tx_buffer {int flags; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  ef4_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 int /*<<< orphan*/  EF4_POPULATE_QWORD_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EF4_TX_BUF_CONT ; 
 int EF4_TX_BUF_OPTION ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BUF_ADDR ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BUF_REGION ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_BYTE_COUNT ; 
 int /*<<< orphan*/  FSF_AZ_TX_KER_CONT ; 
 int /*<<< orphan*/  ef4_farch_notify_tx_desc (struct ef4_tx_queue*) ; 
 int /*<<< orphan*/  ef4_farch_push_tx_desc (struct ef4_tx_queue*,int /*<<< orphan*/ *) ; 
 scalar_t__ ef4_nic_may_push_tx_desc (struct ef4_tx_queue*,unsigned int) ; 
 int /*<<< orphan*/ * ef4_tx_desc (struct ef4_tx_queue*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

void ef4_farch_tx_write(struct ef4_tx_queue *tx_queue)
{
	struct ef4_tx_buffer *buffer;
	ef4_qword_t *txd;
	unsigned write_ptr;
	unsigned old_write_count = tx_queue->write_count;

	tx_queue->xmit_more_available = false;
	if (unlikely(tx_queue->write_count == tx_queue->insert_count))
		return;

	do {
		write_ptr = tx_queue->write_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[write_ptr];
		txd = ef4_tx_desc(tx_queue, write_ptr);
		++tx_queue->write_count;

		EF4_BUG_ON_PARANOID(buffer->flags & EF4_TX_BUF_OPTION);

		/* Create TX descriptor ring entry */
		BUILD_BUG_ON(EF4_TX_BUF_CONT != 1);
		EF4_POPULATE_QWORD_4(*txd,
				     FSF_AZ_TX_KER_CONT,
				     buffer->flags & EF4_TX_BUF_CONT,
				     FSF_AZ_TX_KER_BYTE_COUNT, buffer->len,
				     FSF_AZ_TX_KER_BUF_REGION, 0,
				     FSF_AZ_TX_KER_BUF_ADDR, buffer->dma_addr);
	} while (tx_queue->write_count != tx_queue->insert_count);

	wmb(); /* Ensure descriptors are written before they are fetched */

	if (ef4_nic_may_push_tx_desc(tx_queue, old_write_count)) {
		txd = ef4_tx_desc(tx_queue,
				  old_write_count & tx_queue->ptr_mask);
		ef4_farch_push_tx_desc(tx_queue, txd);
		++tx_queue->pushes;
	} else {
		ef4_farch_notify_tx_desc(tx_queue);
	}
}