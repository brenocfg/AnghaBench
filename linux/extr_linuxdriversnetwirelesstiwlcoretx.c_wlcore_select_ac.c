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
typedef  scalar_t__ u32 ;
struct wl1271 {scalar_t__* tx_allocated_pkts; scalar_t__* tx_queue_count; } ;

/* Variables and functions */
 int NUM_TX_QUEUES ; 
 int wl1271_tx_get_queue (int) ; 

__attribute__((used)) static int wlcore_select_ac(struct wl1271 *wl)
{
	int i, q = -1, ac;
	u32 min_pkts = 0xffffffff;

	/*
	 * Find a non-empty ac where:
	 * 1. There are packets to transmit
	 * 2. The FW has the least allocated blocks
	 *
	 * We prioritize the ACs according to VO>VI>BE>BK
	 */
	for (i = 0; i < NUM_TX_QUEUES; i++) {
		ac = wl1271_tx_get_queue(i);
		if (wl->tx_queue_count[ac] &&
		    wl->tx_allocated_pkts[ac] < min_pkts) {
			q = ac;
			min_pkts = wl->tx_allocated_pkts[q];
		}
	}

	return q;
}