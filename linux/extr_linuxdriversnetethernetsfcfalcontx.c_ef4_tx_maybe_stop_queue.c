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
struct ef4_tx_queue {int /*<<< orphan*/  core_txq; void* old_read_count; void* insert_count; int /*<<< orphan*/  read_count; struct ef4_nic* efx; } ;
struct ef4_nic {unsigned int txq_stop_thresh; unsigned int txq_entries; int /*<<< orphan*/  loopback_selftest; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct ef4_tx_queue* ef4_tx_queue_partner (struct ef4_tx_queue*) ; 
 scalar_t__ likely (int) ; 
 unsigned int max (void*,void*) ; 
 int /*<<< orphan*/  netif_tx_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void ef4_tx_maybe_stop_queue(struct ef4_tx_queue *txq1)
{
	/* We need to consider both queues that the net core sees as one */
	struct ef4_tx_queue *txq2 = ef4_tx_queue_partner(txq1);
	struct ef4_nic *efx = txq1->efx;
	unsigned int fill_level;

	fill_level = max(txq1->insert_count - txq1->old_read_count,
			 txq2->insert_count - txq2->old_read_count);
	if (likely(fill_level < efx->txq_stop_thresh))
		return;

	/* We used the stale old_read_count above, which gives us a
	 * pessimistic estimate of the fill level (which may even
	 * validly be >= efx->txq_entries).  Now try again using
	 * read_count (more likely to be a cache miss).
	 *
	 * If we read read_count and then conditionally stop the
	 * queue, it is possible for the completion path to race with
	 * us and complete all outstanding descriptors in the middle,
	 * after which there will be no more completions to wake it.
	 * Therefore we stop the queue first, then read read_count
	 * (with a memory barrier to ensure the ordering), then
	 * restart the queue if the fill level turns out to be low
	 * enough.
	 */
	netif_tx_stop_queue(txq1->core_txq);
	smp_mb();
	txq1->old_read_count = READ_ONCE(txq1->read_count);
	txq2->old_read_count = READ_ONCE(txq2->read_count);

	fill_level = max(txq1->insert_count - txq1->old_read_count,
			 txq2->insert_count - txq2->old_read_count);
	EF4_BUG_ON_PARANOID(fill_level >= efx->txq_entries);
	if (likely(fill_level < efx->txq_stop_thresh)) {
		smp_mb();
		if (likely(!efx->loopback_selftest))
			netif_tx_start_queue(txq1->core_txq);
	}
}