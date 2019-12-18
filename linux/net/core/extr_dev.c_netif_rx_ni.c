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
 int /*<<< orphan*/  do_softirq () ; 
 scalar_t__ local_softirq_pending () ; 
 int netif_rx_internal (struct sk_buff*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  trace_netif_rx_ni_entry (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_netif_rx_ni_exit (int) ; 

int netif_rx_ni(struct sk_buff *skb)
{
	int err;

	trace_netif_rx_ni_entry(skb);

	preempt_disable();
	err = netif_rx_internal(skb);
	if (local_softirq_pending())
		do_softirq();
	preempt_enable();
	trace_netif_rx_ni_exit(err);

	return err;
}