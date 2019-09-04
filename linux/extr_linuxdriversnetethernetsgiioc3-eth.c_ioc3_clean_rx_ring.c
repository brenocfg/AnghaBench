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
struct sk_buff {scalar_t__ data; } ;
struct ioc3_private {int rx_ci; size_t rx_pi; struct sk_buff** rx_skbs; int /*<<< orphan*/ * rxr; } ;
struct ioc3_erxbuf {scalar_t__ w0; } ;

/* Variables and functions */
 scalar_t__ RX_OFFSET ; 

__attribute__((used)) static inline void ioc3_clean_rx_ring(struct ioc3_private *ip)
{
	struct sk_buff *skb;
	int i;

	for (i = ip->rx_ci; i & 15; i++) {
		ip->rx_skbs[ip->rx_pi] = ip->rx_skbs[ip->rx_ci];
		ip->rxr[ip->rx_pi++] = ip->rxr[ip->rx_ci++];
	}
	ip->rx_pi &= 511;
	ip->rx_ci &= 511;

	for (i = ip->rx_ci; i != ip->rx_pi; i = (i+1) & 511) {
		struct ioc3_erxbuf *rxb;
		skb = ip->rx_skbs[i];
		rxb = (struct ioc3_erxbuf *) (skb->data - RX_OFFSET);
		rxb->w0 = 0;
	}
}