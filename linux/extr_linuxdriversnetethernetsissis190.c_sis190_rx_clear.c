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
struct sis190_private {scalar_t__ RxDescRing; int /*<<< orphan*/ * Rx_skbuff; } ;

/* Variables and functions */
 unsigned int NUM_RX_DESC ; 
 int /*<<< orphan*/  sis190_free_rx_skb (struct sis190_private*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sis190_rx_clear(struct sis190_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_DESC; i++) {
		if (!tp->Rx_skbuff[i])
			continue;
		sis190_free_rx_skb(tp, tp->Rx_skbuff + i, tp->RxDescRing + i);
	}
}