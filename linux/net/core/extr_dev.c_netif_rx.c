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

/* Variables and functions */
 int netif_rx_internal (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_netif_rx_entry (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_netif_rx_exit (int) ; 

int netif_rx(struct sk_buff *skb)
{
	int ret;

	trace_netif_rx_entry(skb);

	ret = netif_rx_internal(skb);
	trace_netif_rx_exit(ret);

	return ret;
}