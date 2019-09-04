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
struct wl1271 {int /*<<< orphan*/  flags; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/ * tx_queue_count; int /*<<< orphan*/  dummy_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_DUMMY_PACKET_PENDING ; 
 int /*<<< orphan*/  WL1271_FLAG_FW_TX_BUSY ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_tx_get_queue (int /*<<< orphan*/ ) ; 
 int wlcore_tx_work_locked (struct wl1271*) ; 

int wl1271_tx_dummy_packet(struct wl1271 *wl)
{
	unsigned long flags;
	int q;

	/* no need to queue a new dummy packet if one is already pending */
	if (test_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags))
		return 0;

	q = wl1271_tx_get_queue(skb_get_queue_mapping(wl->dummy_packet));

	spin_lock_irqsave(&wl->wl_lock, flags);
	set_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags);
	wl->tx_queue_count[q]++;
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	/* The FW is low on RX memory blocks, so send the dummy packet asap */
	if (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags))
		return wlcore_tx_work_locked(wl);

	/*
	 * If the FW TX is busy, TX work will be scheduled by the threaded
	 * interrupt handler function
	 */
	return 0;
}