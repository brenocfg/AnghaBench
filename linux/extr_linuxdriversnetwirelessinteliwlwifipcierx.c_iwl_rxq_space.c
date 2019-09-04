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
struct iwl_rxq {int queue_size; int read; int write; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int iwl_rxq_space(const struct iwl_rxq *rxq)
{
	/* Make sure rx queue size is a power of 2 */
	WARN_ON(rxq->queue_size & (rxq->queue_size - 1));

	/*
	 * There can be up to (RX_QUEUE_SIZE - 1) free slots, to avoid ambiguity
	 * between empty and completely full queues.
	 * The following is equivalent to modulo by RX_QUEUE_SIZE and is well
	 * defined for negative dividends.
	 */
	return (rxq->read - rxq->write - 1) & (rxq->queue_size - 1);
}