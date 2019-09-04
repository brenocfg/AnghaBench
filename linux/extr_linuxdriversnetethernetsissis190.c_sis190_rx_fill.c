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
typedef  unsigned int u32 ;
struct sis190_private {scalar_t__* Rx_skbuff; scalar_t__ RxDescRing; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int NUM_RX_DESC ; 
 scalar_t__ sis190_alloc_rx_skb (struct sis190_private*,scalar_t__) ; 

__attribute__((used)) static u32 sis190_rx_fill(struct sis190_private *tp, struct net_device *dev,
			  u32 start, u32 end)
{
	u32 cur;

	for (cur = start; cur < end; cur++) {
		unsigned int i = cur % NUM_RX_DESC;

		if (tp->Rx_skbuff[i])
			continue;

		tp->Rx_skbuff[i] = sis190_alloc_rx_skb(tp, tp->RxDescRing + i);

		if (!tp->Rx_skbuff[i])
			break;
	}
	return cur - start;
}