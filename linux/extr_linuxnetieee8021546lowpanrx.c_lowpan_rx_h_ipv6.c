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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  lowpan_rx_result ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_QUEUED ; 
 int /*<<< orphan*/  lowpan_is_ipv6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

lowpan_rx_result lowpan_rx_h_ipv6(struct sk_buff *skb)
{
	if (!lowpan_is_ipv6(*skb_network_header(skb)))
		return RX_CONTINUE;

	/* Pull off the 1-byte of 6lowpan header. */
	skb_pull(skb, 1);
	return RX_QUEUED;
}