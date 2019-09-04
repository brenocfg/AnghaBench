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
struct efx_tx_queue {unsigned int write_count; scalar_t__ empty_read_count; } ;

/* Variables and functions */
 int __efx_nic_tx_is_empty (struct efx_tx_queue*,unsigned int) ; 

__attribute__((used)) static inline bool efx_nic_may_push_tx_desc(struct efx_tx_queue *tx_queue,
					    unsigned int write_count)
{
	bool was_empty = __efx_nic_tx_is_empty(tx_queue, write_count);

	tx_queue->empty_read_count = 0;
	return was_empty && tx_queue->write_count - write_count == 1;
}