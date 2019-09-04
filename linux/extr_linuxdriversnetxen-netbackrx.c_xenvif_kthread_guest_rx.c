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
struct xenvif_queue {scalar_t__ id; int /*<<< orphan*/  rx_queue; struct xenvif* vif; } ;
struct xenvif {scalar_t__ stall_timeout; scalar_t__ disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xenvif_carrier_off (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_queue_carrier_off (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_queue_carrier_on (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_rx_action (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_rx_queue_drop_expired (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_rx_queue_purge (struct xenvif_queue*) ; 
 scalar_t__ xenvif_rx_queue_ready (struct xenvif_queue*) ; 
 scalar_t__ xenvif_rx_queue_stalled (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_wait_for_rx_work (struct xenvif_queue*) ; 

int xenvif_kthread_guest_rx(void *data)
{
	struct xenvif_queue *queue = data;
	struct xenvif *vif = queue->vif;

	if (!vif->stall_timeout)
		xenvif_queue_carrier_on(queue);

	for (;;) {
		xenvif_wait_for_rx_work(queue);

		if (kthread_should_stop())
			break;

		/* This frontend is found to be rogue, disable it in
		 * kthread context. Currently this is only set when
		 * netback finds out frontend sends malformed packet,
		 * but we cannot disable the interface in softirq
		 * context so we defer it here, if this thread is
		 * associated with queue 0.
		 */
		if (unlikely(vif->disabled && queue->id == 0)) {
			xenvif_carrier_off(vif);
			break;
		}

		if (!skb_queue_empty(&queue->rx_queue))
			xenvif_rx_action(queue);

		/* If the guest hasn't provided any Rx slots for a
		 * while it's probably not responsive, drop the
		 * carrier so packets are dropped earlier.
		 */
		if (vif->stall_timeout) {
			if (xenvif_rx_queue_stalled(queue))
				xenvif_queue_carrier_off(queue);
			else if (xenvif_rx_queue_ready(queue))
				xenvif_queue_carrier_on(queue);
		}

		/* Queued packets may have foreign pages from other
		 * domains.  These cannot be queued indefinitely as
		 * this would starve guests of grant refs and transmit
		 * slots.
		 */
		xenvif_rx_queue_drop_expired(queue);

		cond_resched();
	}

	/* Bin any remaining skbs */
	xenvif_rx_queue_purge(queue);

	return 0;
}