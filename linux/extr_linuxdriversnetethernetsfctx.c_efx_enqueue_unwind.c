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
struct efx_tx_queue {unsigned int insert_count; } ;
struct efx_tx_buffer {int dummy; } ;

/* Variables and functions */
 struct efx_tx_buffer* __efx_tx_queue_get_insert_buffer (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_dequeue_buffer (struct efx_tx_queue*,struct efx_tx_buffer*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void efx_enqueue_unwind(struct efx_tx_queue *tx_queue,
			       unsigned int insert_count)
{
	struct efx_tx_buffer *buffer;
	unsigned int bytes_compl = 0;
	unsigned int pkts_compl = 0;

	/* Work backwards until we hit the original insert pointer value */
	while (tx_queue->insert_count != insert_count) {
		--tx_queue->insert_count;
		buffer = __efx_tx_queue_get_insert_buffer(tx_queue);
		efx_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);
	}
}